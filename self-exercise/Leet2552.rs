/**
 * 2552. Count Quadraplets
 * https://leetcode.com/problems/count-quadraplets/
 * Solved with Rust, time complexity: O(n^2)
 */

struct Solution;

impl Solution {
    /** 算法思想
     * 算法中，找题中所述四元组实际上就是找两个上升三元组的组合
     * 例如：[1, 2, 6, 4, 5]这样的列表，有[1, 6, 4], [1, 6, 5]这样的三元组，
     * 这样的上升三元组必满足有一个相同的中心
     * 则形成四元组[1, 6, 4, 5]
     */
    pub fn count_quadruplets(nums: Vec<i32>) -> i64 {
        let mut ans: i64 = 0;
        let mut cnt = vec![0; nums.len()];  // 存储以每个位置位中心的三元组数量
        // 找升序三元组
        for rgt in 0..nums.len() {    // rgt为右边界
            let mut tmp = 0;    // 存储以rgt为右界的升序三元组数量
            for mid in 0..rgt {
                if nums[mid] < nums[rgt] {  // 是三元组
                    ans += cnt[mid];  // 加上以mid为中心的三元组数量
                    tmp += 1;  // 找到已知三元组，三元组数量+1
                } else {
                    cnt[mid] += tmp;    // 以mid为中心rgt为右边界的升序三元组数量累加
                }
            }
        }
        ans
    }
}
 
fn main() {
    let test1 = vec![1, 3, 2, 4, 5];
    let test2 = vec![1, 2, 3, 4];
    assert!(Solution::count_quadruplets(test1) == 2);
    assert!(Solution::count_quadruplets(test2) == 0);
    // 如果不报错则顺利进行到最后
    println!("All test cases pass");
} 