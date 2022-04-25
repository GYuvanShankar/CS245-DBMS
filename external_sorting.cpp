#include <bits/stdc++.h>
int buffer;
int record_page;
int record;
std::vector<std::vector<int>> file;
int main() {
    std::cin>>buffer>>record_page>>record;
    for(int i=0;i<record/record_page+1;i++)
    {
        std::vector<int> a; file.push_back(a);
    }
    for(int i=0;i<record;i++)
    {
        int a=i/record_page;
        int x;std::cin>>x;
        file[a].push_back(x);
    }
    for(int i=0;i<file.size();i++)
    {
        std::sort(file[i].begin(),file[i].end());
    }
    while(file.size()>1)
    {
        int t=file.size()/buffer;int u=file.size()%buffer;
        for(int k=0;k<t;k++) {
            std::vector<int> a;
            for (int i = 0; i < buffer; i++) {
                for (int j = 0; j < file[i].size(); j++) {
                    a.push_back(file[i][j]);
                }
            }
            std::sort(a.begin(),a.end());
            file.erase(file.begin(),file.begin()+buffer);
            file.push_back(a);
        }

        std::vector<int> a;
        for(int i=0;i<u;i++)
        {
            for(int j=0;j<file[i].size();j++)
            {
                a.push_back(file[i][j]);
            }
        }
        std::sort(a.begin(),a.end());
        file.erase(file.begin(),file.begin()+u);
        file.push_back(a);
    }
    for(int i=0;i<file[0].size();i++)
    {
        std::cout<<file[0][i]<<std::endl;
    }
}
