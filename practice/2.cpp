#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// 1. ORIGINAL BOILERPLATE STRUCTS MUST GO FIRST
struct Zone {
    string zone_id;
    string zone_name;
    string zone_type;
    int expected_loss_percent;
    int input_index;
};

struct SupplyLog {
    string supply_id;
    string zone_id;
    int supply_day;
    int supplied_litres;
};

struct MeterReading {
    string reading_id;
    string zone_id;
    string meter_id;
    int reading_day;
    int consumed_litres;
    string meter_type;
};

struct LeakageReport {
    string report_id;
    string zone_id;
    int report_day;
    string severity;
};

struct MaintenanceLog {
    string maintenance_id;
    string zone_id;
    int maintenance_day;
    string maintenance_type;
};


// Structure to hold aggregated calculations for each zone
struct ZoneInfo {
    string zone_name;
    int expected_loss_percent = 0;
    int input_index = 0;

    long long totalSuppliedLitres = 0;
    long long totalConsumedLitres = 0;
    int highLeakageCount = 0;
    int mediumHighLeakageCount = 0;
    
    // Initialized to a very small number safely below valid input limits (-10^6)
    int latestMaintenanceDay = -2000000000;
    string latestMaintenanceType = "NONE";

    long long waterLossLitres = 0;
    long long actualLossPercent = 0;
    int anomalyScore = 0;
    string status = "";
};

string solve(int reference_day, vector<Zone>& zones, vector<SupplyLog>& supply_logs, vector<MeterReading>& meter_readings, vector<LeakageReport>& leakage_reports, vector<MaintenanceLog>& maintenance_logs) {
    
    // Valid categories mapped as defined implicitly in samples and instructions
    unordered_set<string> valid_meters = {"HOUSEHOLD", "COMMERCIAL", "INDUSTRIAL"};
    unordered_set<string> valid_severities = {"LOW", "MEDIUM", "HIGH"};
    unordered_set<string> valid_maintenances = {"INSPECTION", "REPAIR", "SHUTDOWN"};

    unordered_map<string, int> zone_id_to_idx;
    vector<ZoneInfo> z_info(zones.size());

    // 1. Initialize our working structures
    for (int i = 0; i < (int)zones.size(); ++i) {
        zone_id_to_idx[zones[i].zone_id] = i;
        z_info[i].zone_name = zones[i].zone_name;
        z_info[i].expected_loss_percent = zones[i].expected_loss_percent;
        z_info[i].input_index = zones[i].input_index;
    }

    // 2. Aggregate Valid Supply Logs
    for (const auto& s : supply_logs) {
        if (s.supply_day <= reference_day && s.supplied_litres >= 0) {
            auto it = zone_id_to_idx.find(s.zone_id);
            if (it != zone_id_to_idx.end()) {
                z_info[it->second].totalSuppliedLitres += s.supplied_litres;
            }
        }
    }

    // 3. Aggregate Valid Meter Readings
    for (const auto& m : meter_readings) {
        if (m.reading_day <= reference_day && m.consumed_litres >= 0 && valid_meters.count(m.meter_type)) {
            auto it = zone_id_to_idx.find(m.zone_id);
            if (it != zone_id_to_idx.end()) {
                z_info[it->second].totalConsumedLitres += m.consumed_litres;
            }
        }
    }

    // 4. Process Valid Leakage Reports
    for (const auto& l : leakage_reports) {
        if (l.report_day <= reference_day && valid_severities.count(l.severity)) {
            auto it = zone_id_to_idx.find(l.zone_id);
            if (it != zone_id_to_idx.end()) {
                if (l.severity == "HIGH") {
                    z_info[it->second].highLeakageCount++;
                    z_info[it->second].mediumHighLeakageCount++;
                } else if (l.severity == "MEDIUM") {
                    z_info[it->second].mediumHighLeakageCount++;
                }
            }
        }
    }

    // 5. Track Valid Maintenance Logs
    for (const auto& m : maintenance_logs) {
        if (m.maintenance_day <= reference_day && valid_maintenances.count(m.maintenance_type)) {
            auto it = zone_id_to_idx.find(m.zone_id);
            if (it != zone_id_to_idx.end()) {
                if (m.maintenance_day > z_info[it->second].latestMaintenanceDay) {
                    z_info[it->second].latestMaintenanceDay = m.maintenance_day;
                    z_info[it->second].latestMaintenanceType = m.maintenance_type;
                }
            }
        }
    }

    vector<ZoneInfo> results;
    
    // 6. Calculate Anomalies and Assign Statuses
    for (auto& zi : z_info) {
        zi.waterLossLitres = zi.totalSuppliedLitres - zi.totalConsumedLitres;
        
        if (zi.totalSuppliedLitres == 0) {
            zi.actualLossPercent = 0;
        } else {
            // Integer division accurately reflects standard problem constraints natively in C++
            zi.actualLossPercent = (zi.waterLossLitres * 100) / zi.totalSuppliedLitres;
        }

        zi.anomalyScore = 0;
        
        // Applying Scoring Conditions
        if (zi.actualLossPercent > zi.expected_loss_percent) zi.anomalyScore += 4;
        if (zi.actualLossPercent >= zi.expected_loss_percent + 10) zi.anomalyScore += 4;
        if (zi.waterLossLitres >= 10000) zi.anomalyScore += 3;
        if (zi.highLeakageCount >= 1) zi.anomalyScore += 4;
        if (zi.mediumHighLeakageCount >= 2) zi.anomalyScore += 3;
        if (zi.latestMaintenanceDay == -2000000000) zi.anomalyScore += 2; // Signifies NO valid log exists
        if (zi.latestMaintenanceType == "SHUTDOWN") zi.anomalyScore += 3;
        if (zi.totalConsumedLitres > zi.totalSuppliedLitres) zi.anomalyScore += 5;

        // Determine Final Status
        if (zi.anomalyScore >= 12) {
            zi.status = "CRITICAL";
        } else if (zi.anomalyScore >= 7) {
            zi.status = "WARNING";
        } else {
            zi.status = "NORMAL";
        }

        if (zi.status == "CRITICAL" || zi.status == "WARNING") {
            results.push_back(zi);
        }
    }

    // 7. Sort Using the Specified Tie-Breaking Pipeline
    sort(results.begin(), results.end(), [](const ZoneInfo& a, const ZoneInfo& b) {
        if (a.status != b.status) {
            return a.status < b.status; // Alphabetically "CRITICAL" < "WARNING", achieving desired order
        }
        if (a.anomalyScore != b.anomalyScore) {
            return a.anomalyScore > b.anomalyScore; 
        }
        if (a.actualLossPercent != b.actualLossPercent) {
            return a.actualLossPercent > b.actualLossPercent; 
        }
        return a.input_index < b.input_index;
    });

    if (results.empty()) return "NA";

    // 8. Generate Properly Delimited Format 
    string final_output = "";
    for (size_t i = 0; i < results.size(); ++i) {
        if (i > 0) final_output += "#";
        final_output += results[i].zone_name + "-" + results[i].status + "-" + 
                        to_string(results[i].anomalyScore) + "-" + to_string(results[i].actualLossPercent);
    }

    return final_output;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int reference_day;
    cin >> reference_day;

    int zone_count;
    int supply_count;
    int reading_count;
    int leakage_count;
    int maintenance_count;

    cin >> zone_count;
    cin >> supply_count;
    cin >> reading_count;
    cin >> leakage_count;
    cin >> maintenance_count;

    vector<Zone> zones;
    for (int input_index = 0; input_index < zone_count; input_index++) {
        Zone zone;
        cin >> zone.zone_id >> zone.zone_name >> zone.zone_type >> zone.expected_loss_percent;
        zone.input_index = input_index;
        zones.push_back(zone);
    }

    vector<SupplyLog> supply_logs;
    for (int i = 0; i < supply_count; i++) {
        SupplyLog supply_log;
        cin >> supply_log.supply_id >> supply_log.zone_id >> supply_log.supply_day >> supply_log.supplied_litres;
        supply_logs.push_back(supply_log);
    }

    vector<MeterReading> meter_readings;
    for (int i = 0; i < reading_count; i++) {
        MeterReading meter_reading;
        cin >> meter_reading.reading_id >> meter_reading.zone_id >> meter_reading.meter_id >> meter_reading.reading_day >> meter_reading.consumed_litres >> meter_reading.meter_type;
        meter_readings.push_back(meter_reading);
    }

    vector<LeakageReport> leakage_reports;
    for (int i = 0; i < leakage_count; i++) {
        LeakageReport leakage_report;
        cin >> leakage_report.report_id >> leakage_report.zone_id >> leakage_report.report_day >> leakage_report.severity;
        leakage_reports.push_back(leakage_report);
    }

    vector<MaintenanceLog> maintenance_logs;
    for (int i = 0; i < maintenance_count; i++) {
        MaintenanceLog maintenance_log;
        cin >> maintenance_log.maintenance_id >> maintenance_log.zone_id >> maintenance_log.maintenance_day >> maintenance_log.maintenance_type;
        maintenance_logs.push_back(maintenance_log);
    }

    cout << solve(reference_day, zones, supply_logs, meter_readings, leakage_reports, maintenance_logs) << "\n";

    return 0;
}