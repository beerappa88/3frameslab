#include <bits/stdc++.h>
using namespace std;

class VersionedFile {
private:
    string filename;
    string baseVersion;
    vector<string> deltas;

public:
    VersionedFile(const string& filename) : filename(filename){}

    void setBaseVersion(const string& content){
        baseVersion = content;
    }

    void addDelta(const string& delta){
        deltas.push_back(delta);
    }

    void persist(){
        ofstream file(filename);
        if(file.is_open()){
            file<<baseVersion<<endl;
            for(const auto& delta : deltas){
                file << delta << endl;
            }
            file.close();
            cout<<"File"<<filename<<"persisted successfully"<<endl;
        } 
        else cerr<<"Unable to open file"<<filename<<"for writing"<<endl;
        
    }

    void load(){
        ifstream file(filename);
        deltas.clear();
        if(file.is_open()){
            getline(file, baseVersion);
            string line;
            while(getline(file, line)){
                deltas.push_back(line);
            }
            file.close();
            cout<<"File"<<filename<<"loaded successfully"<<endl;
        } 
        else cerr<<"Unable to open file"<<filename<<"for reading"<<endl;
    }

    string generateVersion() const{
        string versionContent=baseVersion;
        for(const auto& delta : deltas){
            versionContent += delta;
        }
        return versionContent;
    }
};

int main() {
    VersionedFile file("example.txt");
    file.setBaseVersion("Base content.");
    file.addDelta(" This is the delta for version 1.");
    file.addDelta(" This is the delta for version 2.");

    file.persist();

    VersionedFile file2("example.txt");
    file2.load();

    string versionContent = file2.generateVersion();
    cout << "Content of generated version: " << versionContent << endl;

    return 0;
}
