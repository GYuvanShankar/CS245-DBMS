#include <bits/stdc++.h>
struct record
{
    int primary_key;
    int start;
    int end;
};
struct page
{
    std::vector<record> a;
    int capacity;
    int start;
};
std::vector<page> file;
int max=0;
void insert(int size, int pkey)
{
    if(file.empty())
    {
        page p1;
        p1.capacity=16+size+4;
        p1.start=size;
        record r{};
        r.primary_key=pkey;
        r.start=0;
        r.end=size-1;
        p1.a.push_back(r);
        file.push_back(p1);
    }
    else
    {
        int flag=0;
        for(int i=0;i<file.size();i++)
        {
            if(file[i].capacity+4+size<=max)
            {
                flag=1;
                record r1{};
                r1.primary_key=pkey;
                r1.start=file[i].start;
                r1.end=file[i].start+size-1;
                file[i].a.push_back(r1);
                file[i].capacity+=size+4;
                file[i].start=file[i].start+size;
                break;
            }
        }
        if(flag==0)
        {
            page p1;
            p1.capacity=16+size+4;
            p1.start=size;
            record r{};
            r.primary_key=pkey;
            r.start=0;
            r.end=size-1;
            p1.a.push_back(r);
            file.push_back(p1);
        }
    }
}
void display()
{
    std::cout<<file.size()<<" ";
    for(int i=0;i<file.size();i++)
    {
            std::cout<<file[i].a.size()<<" ";

    }
    std::cout<<std::endl;
}
void search(int n)
{
    int flag=0;
    for(int i=0;i<file.size();i++)
    {
        for(int j=0;j<file[i].a.size();j++)
        {
            if(file[i].a[j].primary_key==n)
            {
                std::cout<<i<<" "<<j<<std::endl;
                flag=1;
            }
        }
    }
    if(flag==0)
    {
        std::cout<<-1<<" "<<-1<<std::endl;
    }
}
int main() {

    std::cin>>max;
    int flag=0;
    while(flag==0)
    {
        int c;std::cin>>c;
        switch (c)
        {
            case 1: int size,pkey;std::cin>>size>>pkey;insert(size,pkey);break;
            case 2: display(); break;
            case 3: int n;std::cin>>n;search(n);break;
            case 4: flag=1;break;
            default: flag=1;break;

        }
    }
}
