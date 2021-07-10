using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JumpGame
{
    class DynamicProgrammingSolution : ISolution
    {
        public bool CanJump(int[] nums)
        {
            // edge cases
            if (nums.Length == 1)
                return true;

            if (nums[0] == 0)
                return false;

            int lastReserve = nums[0];

            int length = nums.Length - 1;
            for (int i = 1; i < length; i++)
            {
                lastReserve = nums[i] > lastReserve - 1 ? nums[i] : lastReserve - 1;

                if (lastReserve == 0)
                    return false;
            }

            return true;
        }
    }
}
