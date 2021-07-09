using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ExceptionServices;

namespace NumberOfIslands
{
    class Program
    {
        //https://leetcode.com/problems/number-of-islands/

        private char[][] grid;
        private Queue<Tuple<int, int>> queue = new Queue<Tuple<int, int>>();

        private bool IsValidIslandTerrain(int i, int j)
        {
            if (i < 0 || i >= grid.Length || j < 0 || j >= grid[0].Length)
                return false;

            return grid[i][j] == '1';
        }

        private List<Tuple<int, int>> directions = new List<Tuple<int, int>>()
        {
            new Tuple<int, int>(-1, 0),
            new Tuple<int, int>(0, 1),
            new Tuple<int, int>(1, 0),
            new Tuple<int, int>(0, -1),
        };

        private void CancelIsland(int starti, int startj)
        {

            grid[starti][startj] = '.';
            queue.Enqueue(new Tuple<int, int>(starti, startj));

            while(queue.Count > 0)
            {
                var current = queue.Dequeue();
                var i = current.Item1;
                var j = current.Item2;

                grid[i][j] = '-';

                foreach (var direction in directions)
                {
                    int newi = i + direction.Item1;
                    int newj = j + direction.Item2;

                    if (IsValidIslandTerrain(newi, newj))
                    {
                        grid[newi][newj] = '0';
                        queue.Enqueue(new Tuple<int, int>(newi, newj));
                    }
                }
            }
        }

        public int NumIslands(char[][] grid)
        {
            this.grid = grid;
            int islandsFound = 0;

            for(int i = 0; i < grid.Length; i++)
            {
                for(int j = 0; j < grid[0].Length; j++)
                {
                    if (grid[i][j] == '1')
                    {
                        CancelIsland(i, j);
                        ++islandsFound;
                    }
                }
            }
            
            return islandsFound;
        }

        static void Main(string[] args)
        {
        }
    }
}
