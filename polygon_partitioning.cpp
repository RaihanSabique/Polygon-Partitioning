#include<iostream>
#include <stdlib.h>
#include <fstream>
#include<math.h>
#include<stack>
#include<queue>
#include<vector>

using namespace std;

struct point{
    double x,y;
};

struct CustomCompare
{
    bool operator()(const point& p1, const point& p2)
    {
        if(p1.y==p2.y){return p1.x> p2.x;}
        return p1.y < p2.y;
    }
};

class turnVertice
{
    public:
	point vi,vNext,vPrev;
	string type="";
    point edgeNext[2];
    point edgePrev[2];

    point helper;


    turnVertice()
    {
        vi.x=0.0;
        vi.y=0.0;
        vNext.x=0.0;
        vNext.y=0.0;
        vPrev.x=0.0;
        vPrev.y=0.0;
        helper.x=9999;
        helper.y=9999;
    }


	void setNextEdge(point p1,point p2)
	{
	    vi=p1;
	    vNext=p2;
	    edgeNext[0]=p1;
	    edgeNext[1]=p2;
	}
	void setPrevEdge(point p)
	{
	    vPrev=p;
	    edgePrev[0]=p;
	    edgePrev[1]=vi;
	}

	void setType(string t)
	{
	    type=t;
	}

	void setHelper(point h)
	{
	    helper=h;
	}
	point getHelper()
	{
	    return helper;
	}


	point getVertice()
	{
	    return vi;
	}

	point getNextVertice()
	{
	    return vNext;
	}
	point getPrevVertice()
	{
	    return vPrev;
	}
	string getType()
	{
	    return type;
	}
	point* getEdge()
	{
	    return edgeNext;
	}
};

template<class T>
void printQueue(T& q)
{
    while (!q.empty())
    {
        cout<< q.top().x <<","<<q.top().y<<endl;
        q.pop();
    }
}


int main()
{
    ifstream infile("input1.txt");
    int n;
	double a, b;
	if(infile>>a)
    {
        //cout<<a<<"\n";
        n=a;
    }
    point points[n+1];


    int i=0;
    while (infile >> a >> b)
    {
        //points[i].x=a;
        //points[i].y=b;
        points[i]={a,b};

        //cout<<points[i].x<<","<<points[i].y<<"\n";
        i++;
    }
    points[i]=points[0];

    turnVertice *T;
    T=new turnVertice[n];
    //lines=new turnVertice[n];
    priority_queue<point,vector<point>, CustomCompare > pq;

    for(int i=0;i<n;i++)
    {
        pq.push(points[i]);
        T[i].setNextEdge(points[i],points[i+1]);
        if(i==0){
            T[i].setPrevEdge(points[n-1]);
        }
        else{
            T[i].setPrevEdge(points[i-1]);
        }
    }

    ofstream myfile;
    myfile.open ("output1.txt");

    for(int i=0;i<n;i++)
    {
        if(T[i].getVertice().y>T[i].getPrevVertice().y && T[i].getVertice().y>T[i].getNextVertice().y)
        {
            if(T[i].getPrevVertice().x>T[i].getNextVertice().x){
                T[i].setType("start");
            }
            else
                T[i].setType("split");

        }
        else if(T[i].getVertice().y<T[i].getPrevVertice().y && T[i].getVertice().y<T[i].getNextVertice().y)
        {
            if(T[i].getPrevVertice().x>T[i].getNextVertice().x){
                T[i].setType("merge");
            }
            else
                T[i].setType("end");
        }
        else
            T[i].setType("regular");

        cout<<T[i].getType()<<":"<<i<<endl;
        cout<<T[i].getPrevVertice().x<<","<<T[i].getPrevVertice().y<<endl;
        cout<<T[i].getVertice().x<<","<<T[i].getVertice().y<<endl;
        cout<<T[i].getNextVertice().x<<","<<T[i].getNextVertice().y<<endl;

        myfile<<T[i].getPrevVertice().x<<" "<<T[i].getPrevVertice().y<<" ";
        myfile<<T[i].getVertice().x<<" "<<T[i].getVertice().y<<endl;
        myfile<<T[i].getVertice().x<<" "<<T[i].getVertice().y<<" ";
        myfile<<T[i].getNextVertice().x<<" "<<T[i].getNextVertice().y<<endl;


    }
    myfile.close();

    point digonal[2];


    for(int i=0;i<n;i++)
    {
        if(T[i].getType()=="start")
        {
            T[i].setHelper(T[i].getVertice());
        }
        else{
            if(T[i].getVertice().y>T[i].getNextVertice().y)
            {

            }
        }
    }



    //cout<<pq.top().x<<" "<<pq.top().y<<endl;

    //printQueue(pq);

}
