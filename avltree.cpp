//Including all the basic and necessary libraries
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//Making class named AVL tree which contains all the operation methods

class AVLTree {
public:
    
    /*
        Making a structure Node1 which have all necessary variables 
        indicating the node of the tree
    */
    
    struct Node1 {
        /*
            h refers to height which is used in calculating
            the height of the tree helping in 
            finding the balance factor
        */
        int h;
        
        /*
            Below are declared variables
            data stores the data that is carried in the node of tree
        */
        int data;

        //r (right) indicates to the right side of node
        Node1* r;
        //l (left) indicates to the left side of node 
        Node1* l;
        
         /*
             Below if the constructor for the Node1 having default values and
            is called while the tree in Initialized
         */
        Node1(int value) {

            r = nullptr;
            l= nullptr;
            h = 1;
            data = value;
        }
    };
    
    
    AVLTree() {
        root = nullptr;
        initialized = false;
    }
    /*
        Fristly we have made Initialize method
        which will initialize an enmpty tree
        before insertion
    */
    void Initialize() {
        initialized = true;
    }

   /*
         This the the insert method taking one variable which is the 
        value to be inserted in the tree
   */
    void Insert(int value) {
        /*
            Here we are calling the function with the value and the root 
            where we are supposed to insert and compare
        */
        root = Insert1(value, root);
    }

        /*
            This search the provided node in parameter
            and returns boolean value if it present
        */
    bool Search(int value) {
        Node1* a = root;
        while(a != nullptr) {
            if(value < a->data)
                a = a->l;
            else if(value > a->data)
                a = a->r;
            else if(value == a->data)
                return true;
        }
        return false;
    }

        /*
            Delete method before is called for deleting the value passed
            which check if it exists or not
        */
    void Delete(int value) {
        if(Search(value)) {
            root = Delete1(value, root);
        }
        return;
    }
   
    /*
        Searches the value in range and returns the boolean value
        parameters passed are a= small, b= high and ot is 
        dynamic array as output
    */
    bool Search(int a, int b, vector<int>& ot) {
        //calling find range for the search in range
        FindRange(a, b, ot, root);
        if(ot.size() > 0)
            return true;
        return false;
    }


        /*
            BF refres to Balance Factor which is being calculated
            below using the height method already declared
            This will help to know if rotation is needed
        */
    int BF(Node1* n) {
        //As before if node is null then returning zero
        if(n == nullptr)
            return 0;
        /*
            else calling the height method for left 
            and right node and getting Balance factor
        */
        return Calh(n->l) - Calh(n->r);
    }

    /*
        Here we are calculating the height of the node
        passed in the parameter
    */
    int Calh(Node1* n) {
        /*
            if the node in null then
            the height will be returning zero
        */
        if(n == nullptr)
            return 0;
        //else height of node
        return n->h;
    }
    
    /*
        Below is destructor defined for clearing the object
        and remove the unnesseary data
    */
     ~AVLTree() {
        RemoveAll(root);
    }

    /*
          After the initial Insert method is called the below 
          mentioned methos is called which takes in value to be inserted 
          and node as input
    */
    Node1* Insert1(int value, Node1* n) {
        //if value is null then it will become the root node
        if(n == nullptr) {
            Node1* n1 = new Node1(value);
            return n1;
        }
        //if value is smaller than node data then will call Insert for right node
        else if(value > n->data)
            n->r = Insert1(value, n->r);
        //if value is greater than node data then will call Insert for left node
        else if(value < n->data)
            n->l = Insert1(value, n->l);

       
        //calculating the height of the node
        n->h = max(Calh(n->l), Calh(n->r)) + 1;
        //balancing the tree after insertion
        n = Balancing(n);
        //else return node
        return n;
    }

   
    Node1* Delete1(int value, Node1* n) {
        if(n == nullptr)
            return n;
        else if(value < n->data)
            n->l = Delete1(value, n->l);
        else if(value > n->data)
            n->r = Delete1(value, n->r);
        else {

            Node1* rt = n->r;
            Node1* lt = n->l;
            
            if(rt == nullptr) {
                delete n;
                n = lt;
            }
            else if(lt == nullptr) {
                delete n;
                n = rt;
            }
            
            else {
                Node1* n1 = lt;
                while(n1-> r != nullptr)
                    n1 = n1->r;
                n->data = n1->data;
                n->l = Delete1(n1->data, n->l);
            }
        }

      
        if(n == nullptr)
            return n;
        n->h = max(Calh(n->l), Calh(n->r)) + 1;
        n = Balancing(n);

        return n;
    }

    //This is called after inserting the value to balance the avl tree
    Node1* Balancing(Node1* n) {
        //define a variable balance factor as bf
        int bf = BF(n);

    //if balance factor is less than -1 then 
    if(bf < -1) {

            int a = Calh(n->r);
            if(a == 0 || a == -1){
                n = RR(n);
            }
            //here we have Lr which is LL + RR
            if(a == 1) {
                n->r = LL(n->r);
                n = RR(n);
            }
        }       
        if(bf > 1) {
            int a = Calh(n->l);
          
            if(a == 0 || a== 1) {
                n = LL(n);
            } 
            //here we have to do RL rotation which is RR + LL     
            if(a == -1) {
                n->l = RR(n->l);
                n = LL(n);
            }
        }    
        return n;
    }

    /*
        Making the method for Right rotation which will be called
        in insertion and deletion upon unstable balance factor
    */
    Node1* RR(Node1* a) {
        Node1* b = a->r;
        Node1* c = b->l;

        //swapping
        b->l = a;
        a->r = c;
        //check which is greater and increment
        b->h = max(Calh(b->l), Calh(b->r)) + 1;
        a->h = max(Calh(a->l), Calh(a->r)) + 1;

        return b;
    }

    /*
      Making the method for Right rotation which will be called
      in insertion and deletion upon unstable balance factor
    */
    Node1* LL(Node1* a) {

        Node1* b = a->l;
        Node1* c = b->r;
        //swapping
        b->r = a;
        a->l = c;
        //check which is greater and increment 1
        a->h = max(Calh(a->l), Calh(a->r)) + 1;
        b->h = max(Calh(b->l), Calh(b->r)) + 1;

        return b;
    }

   /*
        Here we check if the tree is initialized or not
        before performing insertion and is check in main method
   */
    bool Initialized() {
        return initialized;
    }
   

    
    void FindRange(int a, int b, vector<int>& ot, Node1* n) {
        if(n == nullptr)
            return;
        if(n->data > b) {
            FindRange(a, b, ot, n->l);
        }
        else if(n->data < a) {
            FindRange(a, b, ot, n->r);
        }
        else {
            FindRange(a, b, ot, n->l);
            ot.push_back(n->data);
            FindRange(a, b, ot, n->r);
        }
        return;
    }

   /*
        Taking care of the garbage for the 
        performance of the code and memory
   */
    void RemoveAll(Node1* n) {
        if(n== nullptr)
            return;
        RemoveAll(n->l);
        RemoveAll(n->r);
        delete n;
    }
private:
    
    /*
        These are the main members of the tree that are 
        initialized here
    */
    Node1* root;
    bool initialized;
};



/*
    Here is the main function which reads the data line by line from the 
    input file and then calls the method as per the file
    after execution it prints the output in the outful file made 
*/
int main(int a, char *res[]) {

    //here cerr is the character error
    if (a!= 2) {
        cerr << "Incorrect format" << endl;
        exit(0);
    }

 /*
        after exectuion the result in moved to output file
        named as output_file.txt
   */
    fstream Output("output_file.txt", ios_base::out);
    if(!Output.is_open()) {
        cerr << "Incorrect creation" << endl;
        exit(0);
    }

    //here we are reading the inputs from the input file
    fstream Input(res[1], ios_base::in);
    if(!Input.is_open()) {
        cerr << "Error encontered while reading the file" << endl;
        exit(0);
    }


    AVLTree tree;

    // Reading the operations from the input file
    string s;
    //getline allows to get read from the input stream
    while(getline(Input, s)) {
        try {
            //finding first occurence of sub-string
            int b = s.find(")");
            int a = s.find("(");
            
            //making substring for above values
            string out = s.substr(a+1, b-a-1);
            string sub = s.substr(0, a);
            

         /*
                If the line is equal to Initialize then
                we will be calling Initialize method
         */
            if(out == "Initialize") {
                tree.Initialize();
            }

            /*
                 Now before moving forward we will check is 
                an empty tree is already made or not
            */
            if(!tree.Initialized()) {
                continue;
            }

            
            //calling Insert method
            else if (out == "Insert") {
                tree.Insert(stoi(sub));
            }
           
           //looking for search and calling the search method
            else if (s.substr(0, a) == "Search") {
                // Search Operation: returns the key if present in the tree else NULL
                if(sub.find(",") == string::npos) {
                    //check if it is present
                    bool present = tree.Search(stoi(sub));
                    //Check it is present and if not then
                    cout << (present ? sub : "NULL") << endl;
                    //giving null in output file
                    Output << (present? sub : "NULL") << endl;
            }
            }

                //Calling Delete method
            else if (out == "Delete") {
                tree.Delete(stoi(sub));
            }
                    else{
                   //last case will be search in range
                    int p = sub.find(",");
                    vector<int> present;
                    // initializing the start and end variable 
                    int start = stoi(sub.substr(0,p));
                    int end = stoi(sub.substr(p+1));
                    //seraching the given values and return boolean output
                    bool found = tree.Search(start, end, present);

                    if(found) {
                        for(unsigned int j = 0; j < present.size()-1; j++) {
                            //if found then giving the result to the outpul file
                            cout << present[j] << ",";
                            Output << present[j] << ",";
                        }
                        cout << present[present.size()-1] << endl;
                        Output << present[present.size()-1] << endl;
                    }
                    //else will be returning null
                    else {
                        cout << "NULL" << endl;
                        Output << "NULL" << endl;
                    }
                }
            }

        // using the catch function to check for any input not valid
        catch(invalid_argument& e) {
            exit(0);
        }
    }

    // Closing the input & output file after reading & writing
    Input.close();
    Output.close();

    return 0;
}