import java.io.*;
import java.util.*;

class Solution
{

    static class SeedChoice
    {
        int id, cost, marginalValue;
        double efficiency;

        SeedChoice(int id, int cost, int mv)
        {
            this.id = id;
            this.cost = cost;
            this.marginalValue = mv;
            this.efficiency = (cost == 0 ? mv : (double)mv / cost);
        }
    }

    static Set<Integer>
    bfsReach(int start, List<List<Integer>> graph, int depth)
    {
        Set<Integer> reached = new HashSet<>();
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{start, 0});
        reached.add(start);

        while (!q.isEmpty())
        {
            int[] curr = q.poll();
            int node = curr[0], d = curr[1];
            if (d == depth)
                continue;

            for (int nei : graph.get(node))
            {
                if (!reached.contains(nei))
                {
                    reached.add(nei);
                    q.add(new int[]{nei, d + 1});
                }
            }
        }
        return reached;
    }

public
    static void main(String[] args) throws Exception
    {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();

        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++)
            graph.add(new ArrayList<>());

        for (int i = 0; i < m; i++)
        {
            int u = sc.nextInt(), v = sc.nextInt();
            graph.get(u).add(v);
            graph.get(v).add(u);
        }

        int numSeeds = sc.nextInt();
        Map<Integer, Integer> seedCost = new HashMap<>();
        for (int i = 0; i < numSeeds; i++)
        {
            int id = sc.nextInt(), cost = sc.nextInt();
            seedCost.put(id, cost);
        }

        int[] values = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            values[i] = sc.nextInt();
        }

        int budget = sc.nextInt();
        int depth = sc.nextInt();

        List<Integer> chosenSeeds = new ArrayList<>();
        Set<Integer> influenced = new HashSet<>();
        int totalValue = 0, totalCost = 0;

        while (true)
        {
            SeedChoice best = null;

            for (Map.Entry<Integer, Integer> entry : seedCost.entrySet())
            {
                int seed = entry.getKey();
                int cost = entry.getValue();

                if (cost + totalCost > budget)
                    continue;

                Set<Integer> reach = bfsReach(seed, graph, depth);
                int marginalValue = 0;
                for (int u : reach)
                {
                    if (!influenced.contains(u))
                    {
                        marginalValue += values[u];
                    }
                }

                if (marginalValue > 0)
                {
                    SeedChoice candidate = new SeedChoice(seed, cost, marginalValue);
                    if (best == null || candidate.efficiency > best.efficiency)
                    {
                        best = candidate;
                    }
                }
            }

            if (best == null)
                break;

            chosenSeeds.add(best.id);
            totalCost += best.cost;

            Set<Integer> newReach = bfsReach(best.id, graph, depth);
            influenced.addAll(newReach);

            totalValue += best.marginalValue;

            seedCost.remove(best.id);
        }

        // Output
        System.out.print("Chosen Seeds: [");
        for (int i = 0; i < chosenSeeds.size(); i++)
        {
            System.out.print(chosenSeeds.get(i));
            if (i + 1 < chosenSeeds.size())
                System.out.print(", ");
        }
        System.out.println("]");
        System.out.println("Total Value: " + totalValue);
        System.out.println("Total Cost: " + totalCost);
    }
}