class Solution:
    def findJudge(self, n: int, trust: list[list[int]]) -> int:
        import copy
    
        if n == 1:
            return 1
        graph = {}  # graph结构 {Person, List[Trust]}
        for relation in trust:
            if relation[1] in graph.keys():
                graph[relation[1]].append(relation[0])
            else:
                graph[relation[1]] = [relation[0]]
        
        judge = []
        for person in graph.keys():
            relation = graph[person]
            if len(relation) == n - 1:
                judge.append(person)
        for person in graph.keys():
            relation = graph[person]
            it = copy.deepcopy(judge)
            for each in it:
                if each in relation:
                    judge.remove(each)

        if len(judge) != 1:
            return -1
        else:
            return judge[0]

def test():
    x = Solution()
    # print(x.findJudge(2, [[1, 2]]))
    # print(x.findJudge(3, [[1, 3], [2, 3]]))
    # print(x.findJudge(3, [[1, 3], [2, 3], [3, 1]]))
    print(x.findJudge(4,[[1,2],[3,2],[1,3],[4,1],[3,1],[2,1],[2,3],[4,3],[4,2],[3,4],[2,4]])) 

if __name__ == '__main__':
    test()