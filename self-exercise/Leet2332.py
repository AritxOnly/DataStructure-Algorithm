class Solution(object):
    def latestTimeCatchTheBus(self, buses: list[int], passengers: list[int], capacity: int) -> int:
        buses.sort()
        passengers.sort()

        pos = 0
        space = 0
        for bus in buses:
            space = capacity
            if pos >= len(passengers):
                break
            while space > 0 and bus >= passengers[pos]:
                pos += 1
                space -= 1
                if pos >= len(passengers):
                    break
            
        pos -= 1
        res = buses[-1] if space > 0 else passengers[pos]
        while res == passengers[pos] and pos >= 0:
            res -= 1
            pos -= 1
        
        return res
    
def main():
    s = Solution()
    print(s.latestTimeCatchTheBus([10, 20], [2, 17, 18, 19], 2))
    print(s.latestTimeCatchTheBus([20, 30, 10], [19, 13, 26, 4, 25, 11, 21], 2))
    print(s.latestTimeCatchTheBus([3, 2], [2], 2))

if __name__ == '__main__':
    main()