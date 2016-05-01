#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <set>
// #include <climits>

// const int INT_MAX=32000;
//Constants used in the Adjacency Matrix
const int NOT_CHECKED=-2;
const int NOT_CONNECTED=-1;
const int INTERSECTING=1;
const int ITSELF=0;
const float MAX_DIST=1000000;

//Defining the bounds of our coordinate space
const int END_OF_X=32000;
const int END_OF_Y=32000;

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
	Point p1,p2;
	// int x1,y1,x2,y2;
};
inline Point operator+(const Point& lhs, const Point& rhs)
{	return {lhs.x+rhs.x,lhs.y+rhs.y};
}
inline Point operator/(const Point& lhs, const int a)
{	return {lhs.x/a,lhs.y/a};
}
bool operator==(const Point& lhs, const Point& rhs)
{	if(lhs.x==rhs.x && lhs.y==rhs.y)
    	return true;
    else
    	return false;
}
bool operator==(const Side& lhs, const Side& rhs)
{	if(lhs.p1==rhs.p1 && lhs.p2==rhs.p2)
    	return true;
    else
    	return false;
}
bool CompareSidesByLeftX(Side s1,Side s2){
	// int left1,left2; //Leftmost x coord in side1 and 2
	// (s1.x1<s1.x2)? left1=s1.x1 : left1=s1.x2;
	// (s2.x1<s2.x2)? left2=s2.x1 : left2=s2.x2;
	if(s1.p1.x<=s2.p1.x)
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

struct CentroidPoint{
		float x,y;
	};

class Polygon{

	vector<int> x,y; //Trying to get it done with vectors
	bool convexity; //true if convex shape, false if not
	vector<Side> sides,sidesOrderedByX; //Storing Sides for easy access
	CentroidPoint cent;
	friend class SetOfPolygons;


public:
	int xmax,xmin,ymax,ymin; //Used to reduce number of comparisions with bounding rectangle
	Polygon(){
		// cent.x=0.0;
		// cent.y=0.0;

	}
	Polygon(vector<int> x1,vector<int> y1);
	bool IsConvex(){
		return convexity;
	}
	vector<Side> GetSides(){
		return sides;
	}
	vector<Side> GetSidesOrderedByX(){
		return sidesOrderedByX;
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

  		cout<<"\nCentroid: ";
  		 printf("%.2f %.2f\n", cent.x,cent.y);//<<cent.x<<','<<cent.y;
  		// cout<<"\nSides";
  		// for(i=0;i<sides.size();++i)
  		// 	PrintSide(sides[i]);
  	}
  	protected:
  		void PrintSide(Side s){
  			cout<<endl<<" x: "<<s.p1.x<<' '<<s.p2.x<<endl<<" y: "<<s.p1.y<<' '<<s.p2.y<<endl;
  		}
  		bool onSegment(Point p, Point q, Point r)
  		{
  		    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
  		        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
  		       return true;
  		 
  		    return false;
  		}
  		int orientation(Point p, Point q, Point r)
  		{
  		    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
  		    // for details of below formula.
  		    long val = (q.y - p.y) * (r.x - q.x) -
  		              (q.x - p.x) * (r.y - q.y);
  		 
  		    if (val == 0) return 0;  // collinear
  		 
  		    return (val > 0)? 1: 2; // clock or counterclock wise
  		}
  		bool doIntersect(Point p1, Point q1, Point p2, Point q2, bool DoingPointInPolyCheck=false)
  		{
  		    // Find the four orientations needed for general and
  		    // special cases
  		    int o1 = orientation(p1, q1, p2);
  		    int o2 = orientation(p1, q1, q2);
  		    int o3 = orientation(p2, q2, p1);
  		    int o4 = orientation(p2, q2, q1);
  		    // cout<<' '<<o1<<o2<<o3<<o4;
  		 
  		    
  		    if(!DoingPointInPolyCheck){ //Not Doing Point in Poly Check
  		    	if ((o1 != o2 && o3 != o4) &&(o1!=0 && o2!=0 && o3!=0 && o4!=0))
  		    		return true;
  		    	else
  		    		return false; //edited
  		    }
  		    // General case (Need to check collinearity when seeing if point in polygon)
  		    if (o1 != o2 && o3 != o4) return true;
  		    // Special Cases
  		    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
  		    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  		 
  		    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
  		    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  		 
  		    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
  		    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  		 
  		     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
  		    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  		 
  		    return false; // Doesn't fall in any of the above cases
  		}

  		bool CheckIfIntersecting(){
  			int i,j; Point p1,p2,p3,p4;
  			for(i=0;i<(x.size()-1);i++){
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
  			for(i=0;i<x.size();i++){
  				if (i==(x.size()-1))
  					sum+=(x[0]-x[i])*(y[0]+y[i]);
  				else
  					sum+=(x[i+1]-x[i])*(y[i+1]+y[i]);
  				// cout<<' '<<sum; 
  			}
  			if (sum>0)
  				return true;
  			else{
  				// cout<<"NOT AC";
  				return false;
  			}
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

  		bool CheckPointInPolygon(Point p){ //Checks if Point p is in Polygon. Lying on edge doesn't count.
  			if(p.x>=xmax || p.x<=xmin || p.y>=ymax || p.y<=ymin) //Is it outside bounding rectangle?
  				return false;
  			Point extreme={p.x,END_OF_Y}; //To make line x=(p.x) 
  			//Now to check number of intersections of x=(p.x) and the sides of the polygon.
  			//If Odd, Point is inside else if even, outside.
  			vector<Side>::const_iterator i=sidesOrderedByX.begin();
  			int count = 0;
  			while(i!=sidesOrderedByX.end()){
  				if(p.x < (i->p1.x) ) //Making use of the Ordering from least x to highest
  					break;
				// Check if the line segment from 'p' to 'extreme' intersects
        		// with the line segment from 'polygon[i]' to 'polygon[next]'
  				if (doIntersect(i->p1, i->p2, p, extreme, true))
  				    {
			            // If the point 'p' is colinear with line segment 'i-next',
			            // then check if it lies on segment. If it lies, return true,
			            // otherwise false
			            if (orientation(i->p1, p, i->p2) == 0){
			            	//goto out;
			            	cout<<"in";
			              return onSegment(i->p1, p, i->p2);
			            }
			 
			            count++;
  				    }
  				    

  				i++;
  			}
  			return count&1; //Same as taking count%2


  		}
	



};

Polygon::Polygon(vector<int> x,vector<int> y){
	Polygon::x=x;
	Polygon::y=y;

	cent.x=0.0;
	cent.y=0.0;
// cout<<cent.x<<','<<cent.y;
	xmax=*max_element(x.begin(),x.end());
	ymax=*max_element(y.begin(), y.end());
	xmin=*min_element(x.begin(), x.end());
	ymin=*min_element(y.begin(), y.end());
	convexity=CheckConvexity();
	int i;Side s;
	for(i=0;i<x.size();i++){
		if(i==(x.size()-1)){
			if(x[i]<x[0])
				s={{x[i],y[i]},{x[0],y[0]}};
			else
				s={{x[0],y[0]},{x[i],y[i]}};
		}
		else{

			if(x[i]<x[i+1])
				s={{x[i],y[i]},{x[i+1],y[i+1]}};
			else
				s={{x[i+1],y[i+1]},{x[i],y[i]}};
		}
		sides.push_back(s);
		cent.x=cent.x+x[i];
		cent.y=cent.y+y[i];

	}
	sidesOrderedByX=sides;
	sort(sidesOrderedByX.begin(), sidesOrderedByX.end(),CompareSidesByLeftX);
	// cout<<cent.x<<','<<cent.y;
	cent.x=cent.x/x.size();
	cent.y=cent.y/x.size();
	// cout<<cent.x<<','<<cent.y;

}

struct edge { int to; float length; };

class SetOfPolygons{
	vector<Polygon> PolyList;
	std::vector<float> distances;
	// used to check intersections, -2 for not checked, -1 for infinity, 1 for Intersecting(see constants)
	vector< vector<int> > AdjacencyMatrix;
	vector< vector<edge> > AdjacencyList;
	int n,DisconnectedPoly;
	bool Disconnected;
public:
	SetOfPolygons(int n){
		SetOfPolygons::n=n;
		PolyList=vector<Polygon>();
		AdjacencyMatrix=vector< vector<int> >(); 
		AdjacencyList=vector< vector<edge> >(n);
		DisconnectedPoly=-1; //-1 to show First Disconnected Poly not Found;
		Disconnected=false; //Assuming not disconnected initially

	}
	void AddPolygon(vector<int> x,vector<int> y){
		PolyList.push_back(Polygon(x,y));
	}
	void AddPolygon(Polygon p){
		PolyList.push_back(p);
	}
	bool IsDisconnected(){
		return Disconnected;
	}
	int DisconnectedPolyNumber(){
		return DisconnectedPoly;
	}
	void PrintPolyList(){
		int i;//float f;
		for (i=0; i < PolyList.size(); ++i){
    		cout << "Polygon"<<i+1;
    		PolyList[i].printCoords();
   //  		f=dijkstra(AdjacencyList,0,i ));
			// if(int(f)==-1){
			// 	Disconnected=true;
			// 	DisconnectedPoly=i+1
			// 	break;
			// }
			// else
			// 	distances.push_back(f);
		}
	}
	void PrintDistances(){
		int i;
		for (i=1; i < PolyList.size(); ++i){
			printf("\n%.2f", distances[i]);
		}
	}
	void PopulateAdjMatrix(){
		int i=0,j; edge e;
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
					row[j]=NOT_CONNECTED;
				else if(CheckPolyIntersect(PolyList[i],PolyList[j])){
					row[j]=INTERSECTING;
					e={j,CentroidDistance(PolyList[i],PolyList[j])};
					// printf("%d, %.2f\n",e.to,e.length);
					AdjacencyList[i].push_back(e);
					e.to=i;
					AdjacencyList[j].push_back(e);
					//cout<<AdjacencyList[i][0].length;
				}
				else
					row[j]=NOT_CONNECTED;
				// if(row[j]==NOT_CHECKED)
				// 	isPolyDisconnected=false;

			}

			 //PrintIntVector(row);
			AdjacencyMatrix.push_back(row);

		}
		SetDistances();
	}
	void SetDistances(){
		int i;float f;
		for (i=0; i < PolyList.size(); ++i){
    		f=dijkstra(AdjacencyList,0,i );
			if(int(f)==-1){
				Disconnected=true;
				DisconnectedPoly=i+1;
				break;
			}
			else
				distances.push_back(f);
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
	bool CheckPolyIntersect(Polygon poly1,Polygon poly2){ //General Polygon Intersection using sweep line
		vector<Side> s1=poly1.GetSidesOrderedByX(),s2=poly2.GetSidesOrderedByX();
		if(s1==s2){ //Polygons are same
			return true;
		}
		//int i;
		Point pTemp;
		// if(poly1.CheckPointInPolygon(pTemp))
		// 	cout<<"Point inside";
		Side sTemp,sInserted;
		// sort(s1.begin(), s1.end(),CompareSidesByLeftX);
		// sort(s2.begin(), s2.end(),CompareSidesByLeftX);
		vector<Side>::const_iterator i,j;
		list< pair<Side,bool> > active_set; //sides through which line is passing
		//bool above is true if belong to poly1, false if belong to poly2
		list< pair<Side,bool> >::iterator k,l;
		// cout<<endl;
		i = s1.begin(); j = s2.begin();
		while(i != s1.end() || j != s2.end()){
			// cout<<"iter"<<(*j).p1.x;
			if(i != s1.end() && j != s2.end()){
				if(CompareSidesByLeftX(*i,*j)){
					active_set.push_back({*i,true});
					++i;
				}
				else{
					active_set.push_back({*j,false});
					++j;

				}
			}
			else if (i != s1.end())
			{
				active_set.push_back({*i,true});
					++i;
			}
			else{
				active_set.push_back({*j,false});
					++j;
			}

			sInserted=active_set.back().first;
			if (sInserted.p1.x>poly2.xmax){
			//	cout<<"exceededPoly2";
				break;}
			else if(sInserted.p1.x>poly1.xmax){
			//	cout<<"exceededPoly1";
				break;}
			  //cout<<"Inserted"<<endl;poly1.PrintSide(sInserted);cout<<endl;
			for(k=active_set.begin();k!=active_set.end();k++){ //To removed side from active set
				sTemp=(*k).first;
				if(sInserted.p1.x==sTemp.p2.x && sInserted.p1.y==sTemp.p2.y){
					active_set.erase(k);
					break;
				}
			}

			for(k=active_set.begin();k!=active_set.end();k++){
				sTemp=k->first;
				 //cout<<"temp"<<endl;poly1.PrintSide(sTemp);//cout<<endl;
				if(poly1.doIntersect(sInserted.p1,sInserted.p2,sTemp.p1,sTemp.p2)){
					return true;
				}
				else if(poly1.doIntersect(sInserted.p1,sInserted.p2,sTemp.p1,sTemp.p2)){
					pTemp=(sInserted.p1+sInserted.p2)/2; //Rough Midpoint
					if(active_set.back().second){
						if(poly2.CheckPointInPolygon(pTemp))
							return true;
					}
					else{
						if(poly1.CheckPointInPolygon(pTemp))
							return true;
					}
				}
			}

		}
		//Now to Check if Polygon is inside the other, at least one point is inside
		// vector<int> x,y;
		// x=poly1.x;y=poly1.y;
		int h=0;
		bool cond=false;
		// if(s1.size()<s2.size()){ //Do for the one with lesser sides first
		while(h<s1.size()){

			if(h==(s1.size()-1))
				cond=poly2.CheckPointInPolygon(s1[h].p2);
			else
				cond=poly2.CheckPointInPolygon(s1[h].p1);
			if(cond)
				return true;
			h++;
		}
		//}
		// else
		while(h<s2.size()){

			if(h==(s2.size()-1))
				cond=poly1.CheckPointInPolygon(s2[h].p2);
			else
				cond=poly1.CheckPointInPolygon(s2[h].p1);
			if(cond)
				return true;
			h++;
		}




		// sTemp=active_set.back().first;
		// 		cout<<"outside"<<endl;p1.PrintSide(*i);p1.PrintSide(*j); p1.PrintSide(sTemp);cout<<endl;
	    return false;
		
		// for(i=0;i<s1.size();i++){

		// }

	}


	float dijkstra(const vector< vector<edge> > &graph, int source, int target) {
	    vector<float> min_distance( graph.size(), MAX_DIST );
	    min_distance[ source ] = 0;
	    set< pair<int,int> > active_vertices;
	    active_vertices.insert( {0,source} );
		vector<edge>::const_iterator i;
	    edge e;
	   // / vector<edge> edge = graph[active_vertices.begin()->second];
	    while (!active_vertices.empty()) {
	        int where = active_vertices.begin()->second;
	        if (where == target) return min_distance[where];
	        active_vertices.erase( active_vertices.begin() );

	        for (i=graph[where].begin();i!=graph[where].end();i++) {
	        	e=(*i);
	            if (min_distance[e.to] > min_distance[where] + e.length) {
	                active_vertices.erase( { min_distance[e.to], e.to } );
	                min_distance[e.to] = min_distance[where] + e.length;
	                active_vertices.insert( { min_distance[e.to], e.to } );
	            }
	        }
	    }
	    return -1;
	}	

	float CentroidDistance(Polygon p1,Polygon p2){
		return sqrt(pow(p1.cent.x-p2.cent.x,2)+pow(p1.cent.y-p2.cent.y,2));
	}


};

int main(int argc, char const *argv[])
{
	int n=0,i=0;
	cin>>n;
    cin.ignore();
	string rawInput;
	vector<string> numbers;
	string line;
	vector<string>::iterator v;
	vector<int> x,y;
	int temp,bad_poly=0;
	bool Found_bad_poly=false;
	SetOfPolygons PolySet(n);
	Polygon P;
	// stringstream iss=stringstream(line);

	while (i<n) {
		getline( cin, line);
		stringstream iss(line);
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
		else{
			// cout<<"BADin PolyProper().";
			goto set_as_bad_poly;
		}
		
		continue;

		set_as_bad_poly:
			if (!Found_bad_poly){
				Found_bad_poly=true;
				bad_poly=i;
			}
		
	}
	 
	// PolySet.PopulateAdjMatrix();
	 // PolySet.PrintPolyList();
	if(Found_bad_poly)
		cout<<"BAD "<<bad_poly;
	else if(PolySet.IsDisconnected())
		cout<<"DISCONNECTED "<<PolySet.DisconnectedPolyNumber();
	else{
		cout<<"CONNECTED";
		PolySet.PrintDistances();
	}


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