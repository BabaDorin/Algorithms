using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace JumpGame
{
    class GreedySolution : ISolution
    {
        public bool CanJump(int[] nums)
        {
            // Find the farthest element we can get to from each start point.
            // If there is a dead-end, just go back.

            nums = new int[] { 2, 3, 1, 1, 4 };

            bool[] usedElements = new bool[nums.Length];
            int currentPosition = 0;

            while(currentPosition < nums.Length - 1)
            {
                while (currentPosition >= 0 && usedElements[currentPosition])
                {
                    currentPosition--;
                }

                if (currentPosition < 0)
                    break;

                usedElements[currentPosition] = true;
                usedElements[0] = true; // True means that we've already jumped the max out of it,
                currentPosition += nums[currentPosition];
            }

            return currentPosition >= nums.Length - 1;
        }
    }
}
