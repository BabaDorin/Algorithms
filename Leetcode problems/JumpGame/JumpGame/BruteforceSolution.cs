using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JumpGame
{
    class BruteforceSolution : ISolution
    {
        public bool CanJump(int[] nums)
        {
            // Bruteforce 

            var visited = new bool[nums.Length];
            // mark the first element as visited

            visited[0] = true;

            // determine if every element from our array is reachable
            for (int i = 0; i < nums.Length; i++)
            {
                // if the current element is un-reachable, it simply means
                // that we cannot access it, so it doesn't make sense to continue
                if (!visited[i]) return false;

                // mark as visited all of the elements that are reachable from this point
                for (int j = 1; j <= nums[i]; j++)
                {
                    if (i + j < nums.Length)
                        visited[i + j] = true;
                }
            }

            // if we reached the end, we're able to get to the last element
            return true;
        }
    }
}
