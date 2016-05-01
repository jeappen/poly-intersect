#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>
#include <algorithm>

//Constants used in the Adjacency Matrix
const int NOT_CHECKED=-2;
const int INFINITY=-1;
const int INTERSECTING=1;
const int ITSELF=0;

using namespace std;

void PrintIntVector(std::vector<int> v){
	std::vector<int>::const_iterator i;
	cout<<endl;
	for ( i = v.begin(); i != v.end(); ++i)
    	std::cout << *i << ' ';
    cout<<endl;
}

inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}
inline bool isValidInput(const std::string & s, int *i){
	if(isInteger(s)){
		*i=atoi(s.c_str());
		if(i<0)
			return false;
		else
			return true;
		
	}
	return false;
}

struct Point{ //Proposed way of storing coordinates
	int x,y;
};
struct Side{ //Proposed way of storing coordinates
	int x1,y1,x2,y2;
};
bool CompareSidesByLeftX(Side s1,Side s2){
	int left1,left2; //Leftmost x coord in side1 and 2
	(s1.x1<s1.x2)? left1=s1.x1 : left1=s1.x2;
	(s2.x1<s2.x2)? left2=s2.x1 : left2=s2.x2;
	if(left1<left2)
		return true;
	else
		return false;
	// bool lr1,lr2;
	// lr1=(s1.x1<s1.x2); //in s1 p1 is to left, p2 is right
	// lr2=(s2.x1<s2.x2); //same in s2
	// if(lr1){
	// 	if(s2.x2<s1.x1 || s2.x1<s1.x1)
	// 		return false;
	// 	else 
	// 		return true;
	// }
	// else
}


class Polygon{

	vector<int> x,y; //Trying to get it done with vectors
	bool convexity; //true if convex shape, false if not
	vector<Side> sides; //Storing Sides for easy access


public:
	int xmax,xmin,ymax,ymin; //Used to reduce number of comparisions with bounding rectangle
	Polygon(){

	}
	Polygon(vector<int> x1,vector<int> y1);
	bool IsConvex(){
		return convexity;
	}
	vector<Side> GetSides(){
		return sides;
	}
	bool isPolyProper(){

		if( !CheckIfAntiClockwise() || CheckIfIntersecting())
			return false;
		else
			return true;
		// !CheckIfAntiClockwise() || CheckIfIntersecting()

	}
	void printCoords(){
		int i;
		(convexity)? cout<<"\nconvex":cout<<"\nnot convex";
		cout<<"\nX CORDS:";
		for(i=0; i<x.size(); ++i)
  			std::cout << x[i] << ' ';
  		cout<<"\nY CORDS:";
  		for(i=0; i<y.size(); ++i)
  			std::cout << y[i] << ' ';
  		cout<<endl;
  		// cout<<"\nSides";
  		// for(i=0;i<sides.size();++i)
  		// 	PrintSide(sides[i]);
  	}
  	protected:
  		void PrintSide(Side s){
  			cout<<endl<<"x: "<<s.x1<<' '<<s.x2<<" y: "<<s.y1<<' '<<s.y2<<endl;
  		}
  		// bool onSegment(Point p, Point q, Point r)
  		// {
  		//     if (q.x < max(p.x, r.x) && q.x > min(p.x, r.x) &&
  		//         q.y < max(p.y, r.y) && q.y > min(p.y, r.y)) //edited >= to >
  		//        return true;
  		 
  		//     return false;
  		// }
  		int orientation(Point p, Point q, Point r)
  		{
  		    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
  		    // for details of below formula.
  		    int val = (q.y - p.y) * (r.x - q.x) -
  		              (q.x - p.x) * (r.y - q.y);
  		 
  		    if (val == 0) return 0;  // colinear
  		 
  		    return (val > 0)? 1: 2; // clock or counterclock wise
  		}
  		bool doIntersect(Point p1, Point q1, Point p2, Point q2)
  		{
  		    // Find the four orientations needed for general and
  		    // special cases
  		    int o1 = orientation(p1, q1, p2);
  		    int o2 = orientation(p1, q1, q2);
  		    int o3 = orientation(p2, q2, p1);
  		    int o4 = orientation(p2, q2, q1);
  		    // cout<<' '<<o1<<o2<<o3<<o4;
  		 
  		    // General case
  		    if ((o1 != o2 && o3 != o4) &&(o1!=0 && o2!=0 && o3!=0 && o4!=0)) return true;
  		    else
  		    	return false; //edited
  		 
  		    // // Special Cases
  		    // // p1, q1 and p2 are colinear and p2 lies on segment p1q1
  		    // if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  		 
  		    // // p1, q1 and p2 are colinear and q2 lies on segment p1q1
  		    // if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  		 
  		    // // p2, q2 and p1 are colinear and p1 lies on segment p2q2
  		    // if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  		 
  		    //  // p2, q2 and q1 are colinear and q1 lies on segment p2q2
  		    // if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  		 
  		    // return false; // Doesn't fall in any of the above cases
  		}

  		// void SortCoordByX(){

  		// }
  		bool CheckIfIntersecting(){
  			int i,j; Point p1,p2,p3,p4;
  			for(i=0;i<(x.size()-1);i++){
  				// if (i==(x.size-1)){
  				// 	p1.x=x[i];p2.x=x[0];
  				// 	p1.y=y[i];p2.y=y[0];
  				// }
  				// else{

  				// }
  				for(j=i+1;j<x.size();j++){
  					p1.x=x[i]; p2.x=x[i+1];
  					p1.y=y[i]; p2.y=y[i+1];
  					if (j==(x.size()-1)){
  						p3.x=x[j];p4.x=x[0];
  						p3.y=y[j];p4.y=y[0];
  					}
  					else{
  						p3.x=x[j]; p4.x=x[j+1];
  						p3.y=y[j]; p4.y=y[j+1];
  					}
  					if (doIntersect(p1,p2,p3,p4)){
  						// cout<<'\n'<<p1.x<<p1.y<<' '<<p2.x<<p2.y<<' '<<p3.x<<p3.y<<' '<<p4.x<<p4.y<<endl;
  						return true;}
  				}
  			}
  			return false;

  		}
  		bool CheckIfAntiClockwise(){
  			long sum=0;
  			int i;
  			for(i=0;i<(x.size()-1);i++){
  				if (i==(x.size()-1))
  					sum+=(x[0]-x[i])*(y[0]+y[i]);
  				else
  					sum+=(x[i+1]-x[i])*(y[i+1]+y[i]);
  			}
  			if (sum>0)
  				return true;
  			else
  				return false;
  		}
  		bool CheckConvexity(){
  			int i,j,l; Point p1,p2,p3;
  			l=x.size();
  			for(i=0;i<l;i++){
  				if(i==l-2){
  					p1.x=x[i]; p2.x=x[i+1];	p3.x=x[0];
  					p1.y=y[i]; p2.y=y[i+1]; p3.y=y[0];
  				}
  				else if(i==l-1){
  					p1.x=x[i]; p2.x=x[0]; p3.x=x[1];
  					p1.y=y[i]; p2.y=y[0]; p3.y=y[1];
  				}
  				else{
	  				p1.x=x[i]; p2.x=x[i+1];	p3.x=x[i+2];
	  				p1.y=y[i]; p2.y=y[i+1]; p3.y=y[i+2];
  				}
  				if (orientation(p1,p2,p3)==2)
  					return false;
  			}
  			return true;



  		};
	



};

Polygon::Polygon(vector<int> x,vector<int> y){
	Polygon::x=x;
	Polygon::y=y;
	xmax=*max_element(x.begin(),x.end());
	ymax=*max_element(y.begin(), y.end());
	xmin=*min_element(x.begin(), x.end());
	ymin=*min_element(y.begin(), y.end());
	convexity=CheckConvexity();
	int i;Side s;
	for(i=0;i<x.size();i++){
		if(i==(x.size()-1))
			s={x[i],y[i],x[0],y[0]};
		else
			s={x[i],y[i],x[i+1],y[i+1]};
		sides.push_back(s);
	}

}

class SetOfPolygons{
	vector<Polygon> PolyList;
	// used to check intersections, -2 for not checked, -1 for infinity, 1 for Intersecting(see constants)
	vector< vector<int> > AdjacencyMatrix;
	int n,DisconnectedPoly;
	bool Disconnected;
public:
	SetOfPolygons(int n){
		SetOfPolygons::n=n;
		PolyList=vector<Polygon>();
		AdjacencyMatrix=vector< vector<int> >(); 
		DisconnectedPoly=-1; //-1 to show First Disconnected Poly not Found;
		Disconnected=false; //Assuming not disconnected initially

	}
	void AddPolygon(vector<int> x,vector<int> y){
		PolyList.push_back(Polygon(x,y));
	}
	void AddPolygon(Polygon p){
		PolyList.push_back(p);
	}
	void PrintPolyList(){
		int i;
		for (i=0; i < PolyList.size(); ++i){
    		cout << "Polygon"<<i+1;
    		PolyList[i].printCoords();
		}
	}
	void PopulateAdjMatrix(){
		int i=0,j;
		// bool isPolyDisconnected=true; //Using Bounding Rectangles to check if graph is definitely disconnected
		for (i=0; i < n; ++i){
			// if(isPolyDisconnected)
			// 	isPolyDisconnected=true;
			vector<int> row=vector<int>(n,NOT_CHECKED);
			row[i]=ITSELF;
			for (j=0; j < i; ++j){
				row[j]=AdjacencyMatrix[j][i];
				// if(row[j]==NOT_CHECKED)
				// 	isPolyDisconnected=false;
			}
			for (j=i+1; j < n; ++j){
				if(!CheckBoundingRectangles(PolyList[i],PolyList[j]))
					row[j]=INFINITY;
				// if(row[j]==NOT_CHECKED)
				// 	isPolyDisconnected=false;

			}

			PrintIntVector(row);
			AdjacencyMatrix.push_back(row);
		}
	}
protected:
	bool CheckBoundingRectangles(Polygon p1,Polygon p2){//If Bounding Rectangles intersect
		bool c1,c2,c3,c4;
		c1=(p1.xmax<=p2.xmin);
		c2=(p2.xmax<=p1.xmin);
		c3=(p1.ymax<=p2.ymin);
		c4=(p2.ymax<=p1.ymin);
		if(c1||c2||c3||c4)
			return false;
		else
			return true;

	}
	bool CheckConvexPolyIntersect(Polygon p1,Polygon p2){
		vector<Side> s1=p1.GetSides(),s2=p2.GetSides();
		//int i;
		sort(s1.begin(), s1.end(),CompareSidesByLeftX);
		sort(s2.begin(), s2.end(),CompareSidesByLeftX);
		vector<Side>::const_iterator i,j;
		list< pair<Side,bool> > active_set;
		// cout<<endl;
		i = s1.begin(); j = s2.begin();
		while(i != s1.end() && j != s2.end()){
			if(CompareSidesByLeftX(*i,*j)){
				active_set.push_back({*i,true});
				++i;
			}
			else{
				active_set.push_back({*j,false});
				++j;

			}
		}
	    cout<<endl;
		
		// for(i=0;i<s1.size();i++){

		// }

	}


};
/*
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

//using namespace std;


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

*/




bool PolyCheck(){
	return true;
}
int main(int argc, char const *argv[])
{
	int n=0,i=0;
	std::cin>>n;
	if (std::cin.fail()) {
    std::cout<<"not an int";
    //if(PolyCheck())
    	//printf("%s\n","youuuuuub" );
    
    }
    cin.ignore(256, '\n');
	string rawInput;
	vector<string> numbers;
	string line;
	vector<string>::iterator v;
	vector<int> x,y;
	int temp,bad_poly=0,x_or_y=1;
	bool Found_bad_poly=false;
	SetOfPolygons PolySet(n);
	Polygon P;

	while (getline( cin, line) && i<n) {
		istringstream iss(line);
		numbers.clear();
		x.clear();
		y.clear();
		while( getline( iss, rawInput, ' ' ) )
			numbers.push_back(rawInput);
		i++;
		
		v = numbers.begin();
		if (numbers.size()%2==1){
			goto set_as_bad_poly;
			}
		else
			while( v != numbers.end()) {
			   	if(isValidInput(*v,&temp)){
			   		if(x.size()==y.size())
			   			x.push_back(temp);
			   		else
			   			y.push_back(temp);
			   		// cout<<"\n xinside:"; PrintIntVector(x);
			   		// cout<<"\n yinside:"; PrintIntVector(y);
			      }
				else
					goto set_as_bad_poly;

			    v++;
			    }
			    // cout<<"\n x:"; PrintIntVector(x);
			    // cout<<"\n y:"; PrintIntVector(y);
		P=Polygon(x,y);
		if(P.isPolyProper())
			PolySet.AddPolygon(P);
		else
			goto set_as_bad_poly;
		
		continue;

		set_as_bad_poly:
			if (!Found_bad_poly){
				Found_bad_poly=true;
				bad_poly=i;
			}
		
	}
	 PolySet.PrintPolyList();
	 PolySet.PopulateAdjMatrix();
	if(Found_bad_poly)
		cout<<"BAD "<<bad_poly;

	//    int i=0;
	// char line[1024], *p, *e;
	// long v;
	// while (fgets(line, sizeof(line), stdin) && i<n) {
	    // p = line;
	//     for (p = line; ; p = e) {
	//         v = strtol(p, &e, 10);
	//         if (p == e)
	//             break;
	//         std::cout<<v; // process v here
	//     }
	//     i++;
	// }




	//std::cout<<n;

	return 0;
}