using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;

namespace ForestFire
{
    class TreeFireSolver
    {
        private int xStart;
        private int yStart;

        private List<List<string>> map;

        private void ReadFromFile()
        {
            using (StreamReader sr = new StreamReader("data.in"))
            {
                int[] startPosition = sr.ReadLine()
                    .Split(' ')
                    .Select(q => int.Parse(q))
                    .ToArray();

                yStart = startPosition[0];
                xStart = startPosition[1];

                map = new List<List<string>>();
                map = sr.ReadToEnd()
                    .Split('\n')
                    .Select(q =>
                    {
                        var final = q;
                        if (q[q.Length - 1] == '\r')
                            final = q.Substring(0, q.Length - 1);

                        return final
                            .ToCharArray()
                            .Select(q => q.ToString())
                            .ToList();
                    })
                    .ToList();

                for(int i = 0; i < map.Count; i++)
                {
                    for(int j = 0; j < map[i].Count(); j++)
                    {
                        Console.Write(map[i][j]);
                    }
                    Console.WriteLine();
                }

                Console.WriteLine();
                Console.WriteLine($"Start position: {yStart} {xStart}");
            }
        }


        public int Solve()
        {
            ReadFromFile();

            queue.Enqueue(new Tuple<int, int, int>(yStart, xStart, 1));
            Burn();

            for (int i = 0; i < map.Count; i++)
            {
                for (int j = 0; j < map[i].Count(); j++)
                {
                    Console.Write(map[i][j]);
                }
                Console.WriteLine();
            }

            return 0;
        }

        private List<Tuple<int, int>> directions = new()
        {
            new Tuple<int, int>(-1, 0),
            new Tuple<int, int>(-1, 1),
            new Tuple<int, int>(0, 1),
            new Tuple<int, int>(1, 1),
            new Tuple<int, int>(1, 0),
            new Tuple<int, int>(1, -1),
            new Tuple<int, int>(0, -1),
            new Tuple<int, int>(-1, -1),
        };

        private Queue<Tuple<int, int, int>> queue = new Queue<Tuple<int, int, int>>();

        private void Burn()
        {
            while(queue.Count > 0)
            {
                var current = queue.Dequeue();
                var i = current.Item1;
                var j = current.Item2;

                map[current.Item1][current.Item2] = current.Item3.ToString();

                var newTime = current.Item3 + 1;
                foreach (var direction in directions)
                {
                    int newi = i + direction.Item1;
                    int newj = j + direction.Item2;

                    if (IsValid(newi, newj))
                    {
                        // Mark the tree as visited
                        map[newi][newj] = "VT";
                        queue.Enqueue(new Tuple<int, int, int>(newi, newj, newTime));
                    }
                }
            }
        }

        private bool IsValid(int i, int j)
        {
            // Boundary validation
            if (i < 0 || i >= map.Count || j < 0 || j >= map[0].Count())
                return false;

            if (map[i][j] == "T")
                return true;

            return false;
        }
    }


    class Program
    {

        static void Main(string[] args)
        {
            var solver = new TreeFireSolver();
            Console.WriteLine(solver.Solve()); 
        }
    }
}
