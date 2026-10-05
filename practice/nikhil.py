def solve(reference_day, experiments, lab_profiles, trial_observations, calibration_logs, peer_validation_studies):
    # 1. Process and store lab profiles
    labs = {}
    for lab_id, lab_name, cert_level, rel_score in lab_profiles:
        labs[lab_id] = {'certification': cert_level, 'reliability': rel_score}

    # 2. Process calibration logs to find the latest valid log per lab
    # Valid calibration logs must be between day 1 and referenceDay inclusive, 
    # and have a status of PASSED or FAILED.
    lab_calibrations = {} 
    for cal_id, lab_id, cal_day, cal_status in calibration_logs:
        if 1 <= cal_day <= reference_day and cal_status in ('PASSED', 'FAILED'):
            if lab_id not in lab_calibrations:
                lab_calibrations[lab_id] = (cal_day, cal_status)
            else:
                # If multiple valid logs exist, use the one with the maximum calibrationDay
                if cal_day >= lab_calibrations[lab_id][0]:
                    lab_calibrations[lab_id] = (cal_day, cal_status)

    # Dictionary to quickly look up an experiment's start_day for validation checks
    exp_start_days = {exp[0]: exp[4] for exp in experiments}

    # 3. Process trial observations
    exp_trials = {exp[0]: [] for exp in experiments}
    for t_id, e_id, t_day, obs_eff, meas_err, status in trial_observations:
        if e_id in exp_start_days:
            s_day = exp_start_days[e_id]
            # Valid trial conditions: between startDay and referenceDay, VALID status, non-negative error
            if s_day <= t_day <= reference_day and status == 'VALID' and meas_err >= 0:
                exp_trials[e_id].append({'obs_eff': obs_eff, 'meas_err': meas_err})

    # 4. Process peer validation studies
    exp_peers = {exp[0]: {'SUPPORTED': 0, 'CONTRADICTED': 0} for exp in experiments}
    for s_id, e_id, v_day, result in peer_validation_studies:
        if e_id in exp_start_days:
            s_day = exp_start_days[e_id]
            # Valid peer study conditions: between startDay and referenceDay, valid result status
            if s_day <= v_day <= reference_day and result in ('SUPPORTED', 'CONTRADICTED', 'INCONCLUSIVE'):
                if result in exp_peers[e_id]:
                    exp_peers[e_id][result] += 1

    results = []

    # 5. Calculate features and evaluate risk score for each experiment
    for exp in experiments:
        e_id, e_name, l_id, res_area, s_day, exp_eff_size, in_idx = exp

        # Lab Profile Features
        cert_level = labs[l_id]['certification']
        rel_score = labs[l_id]['reliability']

        # Latest Calibration Status
        if l_id in lab_calibrations:
            latest_cal = lab_calibrations[l_id][1]
        else:
            latest_cal = "NONE"

        # Trial Features
        trials = exp_trials[e_id]
        valid_trial_count = len(trials)
        
        if valid_trial_count == 0:
            avg_obs = 0
            # Rule: If validTrialCount is 0, use expectedEffectSize as the effectDeviation
            eff_dev = exp_eff_size 
            eff_var = 0
            high_err_cnt = 0
        else:
            sum_obs = sum(t['obs_eff'] for t in trials)
            # Rule: Use integer division //
            avg_obs = sum_obs // valid_trial_count
            eff_dev = abs(exp_eff_size - avg_obs)
            obs_list = [t['obs_eff'] for t in trials]
            eff_var = max(obs_list) - min(obs_list)
            high_err_cnt = sum(1 for t in trials if t['meas_err'] >= 10)

        # Peer Validation Features
        supp_count = exp_peers[e_id]['SUPPORTED']
        contra_count = exp_peers[e_id]['CONTRADICTED']

        # 6. Calculate Replication Risk Score based on condition table
        score = 0
        if valid_trial_count == 0:
            score += 6
        if 0 < valid_trial_count < 3:
            score += 3
        if eff_dev > 20:
            score += 4
        if eff_var > 30:
            score += 4
        if high_err_cnt >= 2:
            score += 3
        if latest_cal == 'FAILED':
            score += 4
        if latest_cal == 'NONE':
            score += 3
        if contra_count > supp_count:
            score += 4
        if contra_count >= 2:
            score += 3
        if rel_score < 60:
            score += 3
        if cert_level == 'BASIC':
            score += 2

        # 7. Determine Risk Level
        if score >= 12:
            level = 'HIGH'
        elif 7 <= score <= 11:
            level = 'MEDIUM'
        else:
            level = 'LOW'

        # Only retain HIGH and MEDIUM risk experiments
        if level in ('HIGH', 'MEDIUM'):
            results.append({
                'name': e_name,
                'level': level,
                'score': score,
                'eff_dev': eff_dev,
                'idx': in_idx
            })

    # If no experiment qualifies, return NA
    if not results:
        return "NA"

    # 8. Sort the results sequence based on the 4 provided conditions
    # 1. HIGH risk before MEDIUM risk (HIGH = 0, MEDIUM = 1)
    # 2. Higher riskScore first (Descending -> -score)
    # 3. Higher effectDeviation first (Descending -> -eff_dev)
    # 4. Original input sequence (Ascending -> idx)
    results.sort(key=lambda x: (
        0 if x['level'] == 'HIGH' else 1,
        -x['score'],
        -x['eff_dev'],
        x['idx']
    ))

    # 9. Format output string
    output_strings = [f"{x['name']}-{x['level']}-{x['score']}-{x['eff_dev']}" for x in results]
    
    return "#".join(output_strings)