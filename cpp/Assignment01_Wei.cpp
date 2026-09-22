// Assignment 1 solutions.
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace problem1 {

struct Interval {
    int start;
    int end;
};

void mergeIntervals(vector<Interval>& intervals) {
    for (size_t lim = intervals.size(); lim > 1; --lim) {
        bool changed = false;
        for (size_t j = 0; j + 1 < lim; ++j) {
            if (intervals[j].start > intervals[j + 1].start) {
                swap(intervals[j], intervals[j + 1]);
                changed = true;
            }
        }
        if (!changed) break;
    }

    size_t i = 0;
    while (i + 1 < intervals.size()) {
        if (intervals[i].end >= intervals[i + 1].start) {
            intervals[i + 1].start = intervals[i].start;
            intervals[i + 1].end =
                max(intervals[i].end, intervals[i + 1].end);
            intervals.erase(intervals.begin() + i);
        } else {
            ++i;
        }
    }
}

int run() {
    cout << "Problem 1: Merge Overlapping Intervals\n";
    cout << "Enter the number of intervals: ";

    int count;
    if (!(cin >> count) || count < 0) {
        cerr << "Invalid interval count. Enter a nonnegative integer.\n";
        return 1;
    }

    vector<Interval> intervals;
    for (int i = 0; i < count; ++i) {
        Interval interval;
        cout << "Interval " << i + 1 << " (start end): ";
        if (!(cin >> interval.start >> interval.end) ||
            interval.start > interval.end) {
            cerr << "Invalid interval. Enter two integers with start <= end.\n";
            return 1;
        }
        intervals.push_back(interval);
    }

    cout << "Input: [";
    for (size_t i = 0; i < intervals.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << '[' << intervals[i].start << ", " << intervals[i].end << ']';
    }
    cout << "]\n";

    mergeIntervals(intervals);

    cout << "Merged intervals: [";
    for (size_t i = 0; i < intervals.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << '[' << intervals[i].start << ", " << intervals[i].end << ']';
    }
    cout << "]\n";
    return 0;
}
}

namespace problem2 {

void countingSort(vector<int>& values) {
    int a = 0, b = 0, c = 0;
    for (int value : values) {
        if (value == 0) {
            ++a;
        } else if (value == 1) {
            ++b;
        } else {
            ++c;
        }
    }

    int i = 0;
    for (int j = 0; j < a; ++j) values[i++] = 0;
    for (int j = 0; j < b; ++j) values[i++] = 1;
    for (int j = 0; j < c; ++j) values[i++] = 2;
}

void dutchNationalFlag(vector<int>& values) {
    const int n = static_cast<int>(values.size());
    int left = 0, i = 0, right = n - 1;

    while (i <= right) {
        if (values[i] == 0) {
            swap(values[i], values[left]);
            ++left;
            ++i;
        } else if (values[i] == 1) {
            ++i;
        } else {
            swap(values[i], values[right]);
            --right;
            // Do not move i here. The swapped value still needs checking.
        }
    }
}

void printArray(const vector<int>& values) {
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << "]\n";
}

int run() {
    cout << "Problem 2: Sort 0, 1, and 2\n"
              << "Choose a method:\n"
              << "1. Counting-based solution\n"
              << "2. Dutch National Flag (one pass)\n"
              << "Your choice: ";
    int method;
    if (!(cin >> method) || (method != 1 && method != 2)) {
        cerr << "Invalid choice. Enter 1 or 2.\n";
        return 1;
    }

    cout << "Enter the number of elements: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size. Enter a nonnegative integer.\n";
        return 1;
    }

    vector<int> values;
    cout << "Enter " << n << " values (only 0, 1, or 2):\n";
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value) || value < 0 || value > 2) {
            cerr << "Invalid element. Only 0, 1, and 2 are allowed.\n";
            return 1;
        }
        values.push_back(value);
    }

    cout << "Input: ";
    printArray(values);
    if (method == 1) {
        countingSort(values);
        cout << "Method: Counting-based solution\n";
    } else {
        dutchNationalFlag(values);
        cout << "Method: Dutch National Flag\n";
    }
    cout << "Sorted array: ";
    printArray(values);
    return 0;
}
}

namespace problem3 {

string largestNumber(const vector<int>& values) {
    if (values.empty()) return "";

    vector<string> strs;
    size_t len = 0;
    for (int value : values) {
        strs.push_back(to_string(value));
        len += strs.back().size();
    }

    for (size_t lim = strs.size(); lim > 1; --lim) {
        bool changed = false;
        for (size_t i = 0; i + 1 < lim; ++i) {
            const string ab = strs[i] + strs[i + 1];
            const string ba = strs[i + 1] + strs[i];
            if (ab < ba) {
                swap(strs[i], strs[i + 1]);
                changed = true;
            }
        }
        if (!changed) break;
    }

    // Avoid results such as 0000.
    if (strs.front() == "0") return "0";

    string ans;
    ans.reserve(len);
    for (const string& s : strs) {
        ans += s;
    }
    return ans;
}

int run() {
    cout << "Problem 3: Largest Number\n"
              << "Enter the number of elements: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size. Enter a nonnegative integer.\n";
        return 1;
    }

    vector<int> values;
    cout << "Enter " << n << " nonnegative integers:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value) || value < 0) {
            cerr << "Invalid element. Enter a nonnegative integer within the int range.\n";
            return 1;
        }
        values.push_back(value);
    }

    cout << "Input: [";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << "]\n";

    const string ans = largestNumber(values);
    cout << "Largest number (string): \"" << ans << "\"\n";
    return 0;
}
}

namespace problem4 {

using LetterCounts = array<size_t, 26>;

vector<vector<string>> groupAnagrams(
    const vector<string>& words) {
    vector<LetterCounts> sigs;
    vector<vector<string>> res;

    for (const string& word : words) {
        LetterCounts cnt{};
        for (char letter : word) {
            ++cnt[static_cast<size_t>(letter - 'a')];
        }

        bool found = false;
        for (size_t j = 0; j < sigs.size(); ++j) {
            if (cnt == sigs[j]) {
                res[j].push_back(word);
                found = true;
                break;
            }
        }
        if (!found) {
            sigs.push_back(cnt);
            res.push_back({word});
        }
    }
    return res;
}

void printWords(const vector<string>& words) {
    cout << '[';
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << '"' << words[i] << '"';
    }
    cout << ']';
}

int run() {
    cout << "Problem 4: Group Anagrams\n"
              << "Enter the number of words: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid count. Enter a nonnegative integer.\n";
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> words;
    cout << "Enter one word per line (lowercase a-z only).\n"
              << "A blank line represents an empty string.\n";
    for (int i = 0; i < n; ++i) {
        cout << "Word " << i + 1 << ": ";
        string word;
        if (!getline(cin, word)) {
            cerr << "Missing word.\n";
            return 1;
        }
        for (char letter : word) {
            if (letter < 'a' || letter > 'z') {
                cerr << "Invalid word. Use only lowercase English letters a-z.\n";
                return 1;
            }
        }
        words.push_back(word);
    }

    cout << "Input: ";
    printWords(words);
    cout << '\n';

    const auto ans = groupAnagrams(words);
    cout << "Anagram groups: [";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i > 0) cout << ", ";
        printWords(ans[i]);
    }
    cout << "]\n";
    return 0;
}
}

namespace problem5 {

struct Meeting {
    int start;
    int end;
};

bool canAttendAllMeetings(vector<Meeting>& meetings) {
    for (size_t lim = meetings.size(); lim > 1; --lim) {
        bool changed = false;
        for (size_t i = 0; i + 1 < lim; ++i) {
            if (meetings[i].start > meetings[i + 1].start) {
                swap(meetings[i], meetings[i + 1]);
                changed = true;
            }
        }
        if (!changed) break;
    }

    for (size_t i = 0; i + 1 < meetings.size(); ++i) {
        // end == next start is not a conflict.
        if (meetings[i].end > meetings[i + 1].start) {
            return false;
        }
    }
    return true;
}

int run() {
    cout << "Problem 5: Meeting Attendance\n"
              << "Enter the number of meetings: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid count. Enter a nonnegative integer.\n";
        return 1;
    }

    vector<Meeting> meetings;
    for (int i = 0; i < n; ++i) {
        cout << "Meeting " << i + 1 << " (start end): ";
        Meeting meeting;
        if (!(cin >> meeting.start >> meeting.end) ||
            meeting.start >= meeting.end) {
            cerr << "Invalid meeting. Enter integers with start < end.\n";
            return 1;
        }
        meetings.push_back(meeting);
    }

    cout << "Input: [";
    for (size_t i = 0; i < meetings.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << '[' << meetings[i].start << ", " << meetings[i].end << ']';
    }
    cout << "]\n";

    const bool ans = canAttendAllMeetings(meetings);
    cout << "Can attend all meetings: " << boolalpha << ans << '\n';
    return 0;
}
}

namespace problem6 {

struct Point {
    int x;
    int y;
    uint64_t distanceSquared;
};

uint64_t squaredDistance(int x, int y) {
    const int64_t xx = x;
    const int64_t yy = y;
    return static_cast<uint64_t>(xx * xx) +
           static_cast<uint64_t>(yy * yy);
}

bool closer(const Point& a, const Point& b) {
    return tie(a.distanceSquared, a.x, a.y) <
           tie(b.distanceSquared, b.x, b.y);
}

vector<Point> closestBySorting(const vector<Point>& points,
                                    size_t k) {
    if (k == 0) return {};
    vector<Point> tmp = points;
    sort(tmp.begin(), tmp.end(), closer);
    return vector<Point>(tmp.begin(), tmp.begin() + k);
}

vector<Point> closestByHeap(const vector<Point>& points,
                                size_t k) {
    if (k == 0) return {};
    // Keep the farthest selected point at the top.
    priority_queue<Point, vector<Point>, decltype(&closer)> heap(closer);
    for (const Point& point : points) {
        heap.push(point);
        if (heap.size() > k) heap.pop();
    }

    vector<Point> res;
    res.reserve(k);
    while (!heap.empty()) {
        res.push_back(heap.top());
        heap.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

void printPoints(const vector<Point>& points) {
    cout << '[';
    for (size_t i = 0; i < points.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << '[' << points[i].x << ", " << points[i].y << ']';
    }
    cout << ']';
}

int run() {
    cout << "Problem 6: K Closest Points to the Origin\n"
              << "1. Sorting\n2. Max heap\nChoose a method: ";
    int method;
    if (!(cin >> method) || (method != 1 && method != 2)) {
        cerr << "Invalid choice. Enter 1 or 2.\n";
        return 1;
    }
    cout << "Enter the number of points: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size. Enter a nonnegative integer.\n";
        return 1;
    }
    cout << "Enter k (0 to " << n << "): ";
    int k;
    if (!(cin >> k) || k < 0 || k > n) {
        cerr << "Invalid k. It must satisfy 0 <= k <= n.\n";
        return 1;
    }
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        cout << "Point " << i + 1 << " (x y): ";
        int x, y;
        if (!(cin >> x >> y)) {
            cerr << "Invalid coordinates. Enter two integers within the int range.\n";
            return 1;
        }
        points.push_back({x, y, squaredDistance(x, y)});
    }
    cout << "Input: ";
    printPoints(points);
    cout << "\nk: " << k << "\nMethod: "
              << (method == 1 ? "Sorting" : "Max heap") << '\n';
    const auto ans = method == 1 ? closestBySorting(points, k)
                                 : closestByHeap(points, k);
    cout << "Closest points: ";
    printPoints(ans);
    cout << '\n';
    return 0;
}
}

namespace problem7 {

struct Frequency {
    int value;
    int count;
};

vector<Frequency> countValues(const vector<int>& values) {
    vector<Frequency> table;
    for (int value : values) {
        bool found = false;
        for (Frequency& cur : table) {
            if (cur.value == value) {
                ++cur.count;
                found = true;
                break;
            }
        }
        if (!found) table.push_back({value, 1});
    }
    return table;
}

vector<int> topKFrequent(vector<Frequency>& table, size_t k) {
    if (k == 0) return {};
    for (size_t lim = table.size(); lim > 1; --lim) {
        bool changed = false;
        for (size_t i = 0; i + 1 < lim; ++i) {
            if (table[i].count < table[i + 1].count ||
                (table[i].count == table[i + 1].count &&
                 table[i].value > table[i + 1].value)) {
                swap(table[i], table[i + 1]);
                changed = true;
            }
        }
        if (!changed) break;
    }

    vector<int> res;
    res.reserve(k);
    for (size_t i = 0; i < k; ++i) res.push_back(table[i].value);
    return res;
}

void printArray(const vector<int>& values) {
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << ']';
}

int run() {
    cout << "Problem 7: Top K Frequent Values\n"
              << "Enter the number of elements: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size. Enter a nonnegative integer.\n";
        return 1;
    }
    vector<int> values;
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            cerr << "Invalid element. Enter an integer within the int range.\n";
            return 1;
        }
        values.push_back(value);
    }

    auto table = countValues(values);
    cout << "Enter k (0 to " << table.size() << "): ";
    int k;
    if (!(cin >> k) || k < 0 ||
        static_cast<size_t>(k) > table.size()) {
        cerr << "Invalid k. It must not exceed the number of distinct values.\n";
        return 1;
    }
    cout << "Input: ";
    printArray(values);
    cout << "\nk: " << k << '\n';
    const auto ans = topKFrequent(table, static_cast<size_t>(k));
    cout << "Top k frequent values: ";
    printArray(ans);
    cout << '\n';
    return 0;
}
}

namespace problem8 {

vector<int> mergeSortedArrays(const vector<vector<int>>& arrays) {
    const size_t k = arrays.size();
    vector<size_t> pos(k, 0);
    vector<int> res;

    while (true) {
        bool found = false;
        size_t who = 0;
        for (size_t i = 0; i < k; ++i) {
            if (pos[i] == arrays[i].size()) continue;
            if (!found || arrays[i][pos[i]] < arrays[who][pos[who]]) {
                who = i;
                found = true;
            }
        }
        if (!found) break;
        res.push_back(arrays[who][pos[who]]);
        ++pos[who];
    }
    return res;
}

void printArray(const vector<int>& values) {
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << ']';
}

int run() {
    cout << "Problem 8: Merge K Sorted Arrays\n"
              << "Enter the number of arrays: ";
    int k;
    if (!(cin >> k) || k < 0) {
        cerr << "Invalid count. Enter a nonnegative integer.\n";
        return 1;
    }
    vector<vector<int>> arrays;
    for (int i = 0; i < k; ++i) {
        cout << "Array " << i + 1 << " size: ";
        int n;
        if (!(cin >> n) || n < 0) {
            cerr << "Invalid size. Enter a nonnegative integer.\n";
            return 1;
        }
        vector<int> values;
        cout << "Enter " << n << " integers in nondecreasing order:\n";
        for (int j = 0; j < n; ++j) {
            int value;
            if (!(cin >> value)) {
                cerr << "Invalid integer.\n";
                return 1;
            }
            if (!values.empty() && value < values.back()) {
                cerr << "Input array must be sorted in nondecreasing order.\n";
                return 1;
            }
            values.push_back(value);
        }
        arrays.push_back(std::move(values));
    }
    cout << "Input: [";
    for (size_t i = 0; i < arrays.size(); ++i) {
        if (i > 0) cout << ", ";
        printArray(arrays[i]);
    }
    cout << "]\n";
    const auto ans = mergeSortedArrays(arrays);
    cout << "Merged array: ";
    printArray(ans);
    cout << '\n';
    return 0;
}
}

namespace problem9 {

int kthLargest(const vector<int>& values, size_t k) {
    if (k == 0 || k > values.size()) {
        throw invalid_argument("k must be between 1 and the array length.");
    }
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (size_t i = 0; i < values.size(); ++i) {
        minHeap.push(values[i]);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

int run() {
    cout << "Problem 9: Kth-Largest Element\nEnter the number of elements: ";
    int n;
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid size. Enter a positive integer.\n";
        return 1;
    }
    vector<int> values;
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            cerr << "Invalid integer.\n";
            return 1;
        }
        values.push_back(value);
    }
    cout << "Enter k (1 to " << n << "): ";
    int k;
    if (!(cin >> k) || k < 1 || k > n) {
        cerr << "Invalid k. It must be between 1 and the array length.\n";
        return 1;
    }
    cout << "Input: [";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << "]\nk = " << k << '\n';
    cout << "Kth-largest element: "
              << kthLargest(values, static_cast<size_t>(k)) << '\n';
    return 0;
}
}

namespace problem10 {

int64_t countInversionsBruteForce(const vector<int>& values) {
    int64_t count = 0;
    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = i + 1; j < values.size(); ++j) {
            if (values[i] > values[j]) ++count;
        }
    }
    return count;
}

int64_t sortAndCount(vector<int>& values, vector<int>& buffer,
                          size_t left, size_t right) {
    if (right - left <= 1) return 0;
    const size_t mid = left + (right - left) / 2;
    int64_t count = sortAndCount(values, buffer, left, mid);
    count += sortAndCount(values, buffer, mid, right);
    size_t i = left, j = mid, out = left;
    while (i < mid && j < right) {
        if (values[i] <= values[j]) {
            buffer[out++] = values[i++];
        } else {
            buffer[out++] = values[j++];
            // All remaining left values form inversions here.
            count += static_cast<int64_t>(mid - i);
        }
    }
    while (i < mid) buffer[out++] = values[i++];
    while (j < right) buffer[out++] = values[j++];
    for (size_t p = left; p < right; ++p) values[p] = buffer[p];
    return count;
}

int64_t countInversionsMergeSort(const vector<int>& values) {
    vector<int> tmp = values;
    vector<int> buffer(values.size());
    return sortAndCount(tmp, buffer, 0, tmp.size());
}

int run() {
    cout << "Problem 10: Count Inversions\n"
              << "1. Merge Sort (primary solution)\n"
              << "2. Brute Force (validation only)\n"
              << "3. Run both and compare (small inputs recommended)\n"
              << "Choose a method: ";
    int method;
    if (!(cin >> method) || method < 1 || method > 3) {
        cerr << "Invalid method. Choose 1, 2, or 3.\n";
        return 1;
    }
    cout << "Enter the number of elements: ";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size. Enter a nonnegative integer.\n";
        return 1;
    }
    vector<int> values;
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            cerr << "Invalid integer.\n";
            return 1;
        }
        values.push_back(value);
    }
    cout << "Input: [";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << values[i];
    }
    cout << "]\n";
    int64_t fast = 0, slow = 0;
    if (method == 1 || method == 3) {
        fast = countInversionsMergeSort(values);
        cout << "Merge Sort inversion count: " << fast << '\n';
    }
    if (method == 2 || method == 3) {
        slow = countInversionsBruteForce(values);
        cout << "Brute Force inversion count: " << slow << '\n';
    }
    if (method == 3) {
        cout << "Validation: " << (fast == slow ? "PASS" : "FAIL") << '\n';
        return fast == slow ? 0 : 1;
    }
    return 0;
}
}

int main() {
    cout << "EECE 7205 Assignment 1\n"
              << "Choose a problem (1-10): ";

    int choice;
    if (!(cin >> choice)) {
        cerr << "Invalid choice.\n";
        return 1;
    }

    switch (choice) {
        case 1: return problem1::run();
        case 2: return problem2::run();
        case 3: return problem3::run();
        case 4: return problem4::run();
        case 5: return problem5::run();
        case 6: return problem6::run();
        case 7: return problem7::run();
        case 8: return problem8::run();
        case 9: return problem9::run();
        case 10: return problem10::run();
        default:
            cerr << "Invalid choice. Enter a number from 1 to 10.\n";
            return 1;
    }
}
