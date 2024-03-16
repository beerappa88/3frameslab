#include <bits/stdc++.h>
using namespace std;

// Function to parse the text file and count words
unordered_map<string, int> parseTextFile(const string& filePath){
    unordered_map<string, int> wordCount;
    ifstream file(filePath);
    string word;
    while (file >> word){
        // Convert word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // Remove non-alphanumeric characters
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalnum(c); }), word.end());
        if(!word.empty())
            ++wordCount[word];
    }
    return wordCount;
}

// Function to find top k words
vector<pair<string, int>> topKWords(const unordered_map<string, int>& wordCount, int k){
    priority_queue<pair<int, string>> maxHeap;
    for(const auto& entry : wordCount){
        maxHeap.push({entry.second, entry.first});
        if(maxHeap.size() > k) maxHeap.pop();
    }
    vector<pair<string, int>> topK;
    while(!maxHeap.empty()){
        topK.push_back({maxHeap.top().second, maxHeap.top().first});
        maxHeap.pop();
    }
    reverse(topK.begin(), topK.end());
    return topK;
}

// Function for fuzzy search
vector<pair<string, int>> fuzzySearch(const string& query, const unordered_map<string, int>& wordCount, int threshold){
    vector<pair<string, int>> matches;
    for(const auto& entry : wordCount){
        const string& word = entry.first;
        if (abs(static_cast<int>(word.length()) - static_cast<int>(query.length())) <= threshold){
            int distance = 0;
            for(size_t i = 0; i < word.length() && i < query.length(); ++i){
                if(word[i] != query[i]) ++distance;
            }
            if(distance <= threshold) matches.push_back({word, entry.second});
        }
    }
    sort(matches.begin(), matches.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    return matches;
}

int main() {
    const string filePath="text_file.txt"; // Path to the text file
    const int k=10; // Top k words
    const string searchQuery="search_query"; // Search query
    const int fuzzyThreshold=1; // Fuzzy search threshold

    unordered_map<string, int> wordCount=parseTextFile(filePath);
    vector<pair<string, int>> topK=topKWords(wordCount, k);

    // Display top k words
    cout<<"Top"<<k<<"words and counts:"<<endl;
    for(const auto& pair : topK){
        cout<<pair.first << ":"<<pair.second<<endl;
    }

    // Perform fuzzy search
    vector<pair<string, int>> searchResults=fuzzySearch(searchQuery, wordCount, fuzzyThreshold);
    cout<<"Fuzzy search results for"<<searchQuery<<"':" << endl;
    for(const auto& pair : searchResults){
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}
