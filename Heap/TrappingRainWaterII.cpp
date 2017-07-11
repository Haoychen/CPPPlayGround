/*
Given an m x n matrix of positive integers representing the height of each unit 
cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 
and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.

The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.


After the rain, water are trapped between the blocks. The total volume of water trapped is 4.
*/

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        // Init m_, n_, is_visited_.
        m_ = heightMap.size();
        if (!m_) {
            return 0;
        }
        n_ = heightMap[0].size();
        if (!n_) {
            return 0;
        }

        is_visited_ = vector<vector<bool>>(m_, vector<bool>(n_, false));

        int trap = 0;

        // Put the cells on the border into min heap.
        for (int i = 0; i < m_; ++i) {
            heap_.emplace(Cell{i, 0, heightMap[i][0]});
            is_visited_[i][0] = true;
            heap_.emplace(Cell{i, n_ - 1, heightMap[i][n_ - 1]});
            is_visited_[i][n_ - 1] = true;
        }
        for (int j = 0; j < n_; ++j) {
            heap_.emplace(Cell{0, j, heightMap[0][j]});
            is_visited_[0][j] = true;
            heap_.emplace(Cell{m_ - 1, j, heightMap[m_ - 1][j]});
            is_visited_[m_ - 1][j] = true;
        }
        const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                {-1, 0}, {1, 0}};
        // BFS with priority queue (min heap)
        while (!heap_.empty()) {
            Cell c = heap_.top();
            heap_.pop();
            for (const auto& d : directions) {
            	trap += fill(heightMap, c.i + d.first, c.j + d.second, c.height);
            }
        }

        return trap;
    }

private:
    int fill(const vector<vector<int>>& heightMap, int i, int j, int height) {
        // Out of border.
        if ( i < 0 || i >= m_ || j < 0 || j >= n_) {
            return 0;
        }

        // Fill unvisited cell.
        if (!is_visited_[i][j]) {
            heap_.emplace(Cell{i, j, max(height, heightMap[i][j])});
            is_visited_[i][j] = true; // Marked as visited.
            return max(0, height - heightMap[i][j]); // Fill in the gap.
        }

        return 0;
    }

    struct Cell {
        int i;
        int j;
        int height;
    };

    struct Compare {
        bool operator()(const Cell& a, const Cell& b) {
            return a.height > b.height;
        }
    };

    int m_;
    int n_;
    vector<vector<bool>> is_visited_;
    priority_queue<Cell ,vector<Cell>, Compare> heap_; // Use min heap to get the lowerest cell.
};
