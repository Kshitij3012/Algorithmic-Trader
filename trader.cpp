/*MAP AND STACK IMPLEMENTED 
RESOURCES: 1) STACK AND MAP CLASS FROM GFG :(i) https://www.geeksforgeeks.org/implementing-stack-using-class-templates-in-cpp/
                                            (ii) https://www.geeksforgeeks.org/build-a-custom-map-using-header-file-in-c/
           2) CHATGPT FOR DEBUGGING THE CLASSES : https://chat.openai.com/
            
*/
#include "receiver.h"
#include <iostream>
#include <cstring>
#include <vector>



#define SIZE 5
 
// Class
// To represent stack using template by class
// taking class in template
template <class T> class Stack {
    // Public access modifier
public:
    // Empty constructor
    Stack();
 
    // Method 1
    // To add element to stack which can be any type
    // using stack push() operation
    void push(T k);
 
    // Method 2
    // To remove top element from stack
    // using pop() operation
    T pop();
 
    // Method 3
    // To print top element in stack
    // using peek() method
    T topElement();
 

    bool isFull();

    bool isEmpty();
 
private:
    // Taking data member top
    int top;
 
    // Initialising stack(array) of given size
    T st[SIZE];
};
 
// Method 6
// To initialise top to
// -1(default constructor)
template <class T> Stack<T>::Stack() { top = -1; }
 
// Method 7
// To add element element k to stack
template <class T> void Stack<T>::push(T k)
{
 
    // Checking whether stack is completely filled
    if (isFull()) {
        // Display message when no elements can be pushed
        // into it
      //  std::cout << "Stack is full\n";
    }
 
    // Inserted element
//std::cout << "Inserted element " << k << std::endl;
 
    // Incrementing the top by unity as element
    // is to be inserted
    top = top + 1;
 
    // Now, adding element to stack
    st[top] = k;
}
 
// Method 8
// To check if the stack is empty
template <class T> bool Stack<T>::isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}
 
// Utility methods
 
// Method 9
// To check if the stack is full or not
template <class T> bool Stack<T>::isFull()
{
    // Till top in inside the stack
    if (top == (SIZE - 1))
        return 1;
    else
 
        // As top can not exceeds th size
        return 0;
}
 
// Method 10
template <class T> T Stack<T>::pop()
{
    // Initialising a variable to store popped element
    T popped_element = st[top];
 
    // Decreasing the top as
    // element is getting out from the stack
    top--;
 
    // Returning the element/s that is/are popped
    return popped_element;
}
 
// Method 11
template <class T> T Stack<T>::topElement()
{
    // Initialising a variable to store top element
    T top_element = st[top];
 
    // Returning the top element
    return top_element;
}
 

template <typename Key, typename Value>
class Map {
    
    
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

        Node* leftRo(Node* mugdha) {
        Node* avani = mugdha->right;
        Node* T2 = avani->left;
        avani->left = mugdha;
        mugdha->right = T2;
        mugdha->height = 1 + std::max(height(mugdha->left), height(mugdha->right));
        avani->height = 1 + std::max(height(avani->left), height(avani->right));
        return avani;
    }

    Node* rightRo(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));
        return x;
    }


  int Alpha(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }
    Node* insert(Node* node, const Key& key, const Value& value) {
        if (node == nullptr)
            return new Node(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value;  // Update the value if the key already exists

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = Alpha(node);

        if (balance > 1) {
            if (key < node->left->key) {
                return rightRo(node);
            } else {
                node->left = leftRo(node->left);
                return rightRo(node);
            }
        }

        if (balance < -1) {
            if (key > node->right->key) {
                return leftRo(node);
            } else {
                node->right = rightRo(node->right);
                return leftRo(node);
            }
        }

        return node;
    }

    Node* Mini(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* erase(Node* node, const Key& key) {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = erase(node->left, key);
        } else if (key > node->key) {
            node->right = erase(node->right, key);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left) ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = Mini(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = erase(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = Alpha(node);

        if (balance > 1) {
            if (Alpha(node->left) >= 0)
                return rightRo(node);
            else {
                node->left = leftRo(node->left);
                return rightRo(node);
            }
        }

        if (balance < -1) {
            if (Alpha(node->right) <= 0)
                return leftRo(node);
            else {
                node->right = rightRo(node->right);
                return leftRo(node);
            }
        }

        return node;
    }

    void clear(Node* node) {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:

    Map() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    void erase(const Key& key) {
        root = erase(root, key);
    }

    Value& operator[](const Key& key) {
        Node* node = fFind(root, key);
        if (node == nullptr) {
            insert(key, Value{}); // Insert with default value if not found
            node = fFind(root, key);
        }
        return node->value;
    }
     Node* end(){
        return nullptr;
    }
    const Value operator[](const Key& key) const {
        Node* node = fFind(root, key);
        if (node == nullptr) {
            return Value{}; // Return default-constructed value if key not found
        }
        return node->value;
    }

    int count(const Key& key) const {
        return (fFind(root, key) != nullptr) ? 1 : 0;
    }
    void clear() {
        clear(root);
        root = nullptr;
    }


    int size() const {
        return size(root);
    }  
    void iterate() {
        if (root != nullptr) {
            iterate(root);
        }
    }
    bool empty() const {
        return root == nullptr;
    }
    Node* find(const Key& key) const {
        return fFind(root, key);
    }

private:
    Node* fFind(Node* node, const Key& key) const {
        if (node == nullptr || node->key == key)
            return node;

        if (key < node->key)
            return fFind(node->left, key);

        return fFind(node->right, key);
    }

    int size(Node* node) const {
        if (node == nullptr)
            return 0;
        return 1 + size(node->left) + size(node->right);
    }

    void iterate(Node* node) {
        if (node->left != nullptr) {
            iterate(node->left);
        }
        std::cout << node->value << ' '<<node->key<<std::endl; 
        if (node->right != nullptr) {
            iterate(node->right);
        }
    }

public:
    class Iterator {
    private:
        Node* current;
        Stack<Node*> nodesStack;

        void pushLeftNodes(Node* node) {
            while (node != nullptr) {
                nodesStack.push(node);
                node = node->left;
            }
        }

    public:
        Iterator(Node* root) {
            current = root;
            pushLeftNodes(current);
        }
        Iterator operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

        Iterator& operator++() {
            if (!nodesStack.isEmpty()) {
                current = nodesStack.topElement();
                nodesStack.pop();
                pushLeftNodes(current->right);
            } else {
                current = nullptr;
            }
            return *this;
        }
        bool operator==(const Iterator& other) const {
    return current == other.current;
}

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        std::pair<Key, Value> operator*() const {
            return std::make_pair(current->key, current->value);
        }
    };
    Iterator begin() const{
        
        return Iterator(root);
    }
    Iterator okokend() const {
        return Iterator(nullptr);
    }

};


// void part1(Map stock) {
    
//     while(message[i]!='$')
        
//     }
//     // Implement part1 logic here
// }
std::vector<std::string> stringugh(std::string message) {
    size_t i = 0;
    std::vector<std::string> order;
    std::string a = "";
    while (i < message.length()) {
        if (message[i] != ' ') {
            a += message[i];
        }
        if ((message[i] == ' ' || message[i] == '#' || i == message.length() - 1) && a!="") {
            order.push_back(a);
            a = "";
        }
        ++i;
    }
    return order;
}
std::pair<Map<std::string, int>, std::vector<int>> findmaximum(
    const std::vector<std::pair<Map<std::string, int>, std::vector<int>>>& w,
    const std::string& keyToFind) {

    std::pair<Map<std::string, int>, std::vector<int>> maxPair;
    int maxValue = 0;//Initialize with //minimum value

    for (const auto& pair : w) {
        const Map<std::string, int>& currentMap = pair.first;//pair.first is map
        Map<std::string, int> avani = currentMap;
        auto it = avani.find(keyToFind);
        if (it != avani.end() && it->value > maxValue) {
            maxValue = it->value;
            maxPair = pair;
        }
    }

    return maxPair;
}
Map<std::string, int> addmap(const Map<std::string, int>& map1, const Map<std::string, int>& map2) {
 
    Map<std::string, int> mergedMap = map1;
    Map<std::string, int> tempmap1 = map1;
    Map<std::string, int> tempmap2 = map2;
    int i=0;
    for (auto it = tempmap2.begin(); it != tempmap2.end(); ++it) {
        if(i==0){++it;}
        i++;
        std::pair<std::string, int> keyValue = *it;
        const std::string& key = keyValue.first;
        int value2 = keyValue.second;
        if (mergedMap.find(key) != mergedMap.end()) {
            
            // Key exists in mergedMap, add the values
            mergedMap[key] += value2;
           

        } else {
            // Key doesn't exist in mergedMap, insert it
           
            mergedMap[key] = value2;
           
        }
        
    }

    return mergedMap;
}



// void deleteit(std::vector<std::pair<Map<std::string,int>,std::vector<int>>>order, std::pair<Map<std::string,int>,std::vector<int>> mpair){
//     int n = order.size();
//     for(int i=0;i<mpair.second.size();i++){
//         for(int j=0;j<n;j++){
//             for(int k=0;k<order[j].second.size();k++){
//                 if(order[j].second[k]==mpair.second[i]){
//                     order.erase(order.begin()+j);
//                 }
//             }
//         }
//     }
// }

void deleteit(std::vector<std::pair<Map<std::string,int>,std::vector<int>>>& order, 
              const std::pair<Map<std::string,int>,std::vector<int>>& mpair) {
    for (const auto& val : mpair.second) {  // Iterate through elements in mpair.second
        for (auto it = order.begin(); it != order.end(); ) {
            const std::vector<int>& currentVector = it->second;

            // Manual find implementation since <algorithm> is not allowed
            auto found = currentVector.end();
            for (auto vec_it = currentVector.begin(); vec_it != currentVector.end(); ++vec_it) {
                if (*vec_it == val) {
                    found = vec_it;
                    break;
                }
            }

            if (found != currentVector.end()) {
                it = order.erase(it); // erase the element from order
            } else {
                ++it;
            }
        }
    }
}

template<typename K, typename V>

bool allValuesZero(const Map<K, V>& myMap) {
    // for (const auto& pair : myMap) {
         Map<std::string, int>mugdha = myMap;
        for(auto it=mugdha.begin(); it!= mugdha.okokend() ; ++it){
            std::pair<std::string, int> pair= *it;
        if (pair.second != 0 && pair.first != "price") {
            return false; 
        }
    }
    return true; 
}

template<typename K, typename V>

bool mapsAreEqual(const Map<K, V>& map1, const Map<K, V>& map2) {
    auto it1 = map1.begin();
    auto it2 = map2.begin();

    if (map1.empty() || map2.empty()) {
        return false;
    }

    while (it1 != map1.okokend() && it2 != map2.okokend()) {

        auto keyvalue1= *it1;
        std::pair<std::string, int> keyvalue2= *it2;
        auto it3= ++it1;
        auto it4=++it2;
        if(it3== map1.okokend() && it4== map2.okokend())break;
        if (keyvalue1.first != keyvalue2.first || keyvalue1.second != keyvalue2.second) {
            return false; 
        }
        ++it1;
        ++it2;
        
    }
++it1;
    // Check if sizes are equal and the last element of map1 has been reached
    return map1.size() == map2.size() && it1 == map1.okokend();
}
std::vector<int> addVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    std::vector<int> result = vec1; 

    result.insert(result.end(), vec2.begin(), vec2.end());

    return result;
}
int p=0;
void makingpermutations(std::string message){
    std::vector<std::pair<Map<std::string,int>,std::vector<int>>> order;
    int id =0;
    std::vector<std::pair<int, std::vector<std::string>>> matrix;
    

    int i=0;

    while(message[i] != '$'){
        std::string a="";
        while(i<message.length() && message[i]!='#'){
            a=a+message[i];
            ++i;
        }
        std::vector<std::string>stock; //stock is the vector having x 1 y -1 z 1 s etc
        std::pair<int,std::vector<std::string>> pair1;
        stock = stringugh(a);

        if(stock[stock.size()-1] == "s") stock[stock.size()-1]= "b"; //taaki hum matrix me value add kar sake
        else stock[stock.size()-1]= "s";

        pair1.first = id; 
        pair1.second=stock;
        matrix.push_back(pair1);
        Map<std::string,int> bform;
        Map<std::string,int> sform;


        if(stock[stock.size()-1] == "s") stock[stock.size()-1]= "b";//back to the original
        else stock[stock.size()-1]= "s";

        for(int g=0; g<stock.size()-2;g=g+2){

            int num = std::stoi(stock[g+1]);

            if(stock[stock.size()-1]=="s"){
                num=num*(-1);                         //where we change the sign
            }
            bform[stock[g]] = num;
        }

        for(int g=0; g<stock.size()-2;g=g+2){

            int num = std::stoi(stock[g+1]);

            if(stock[stock.size()-1]=="b"){
                num=num*(-1);                         //where we change the sign
            }
            sform[stock[g]] = num;
        }
            
        int m = std::stoi(stock[stock.size()-2]);
        if(stock[stock.size()-1]=="s"){
                sform["price"] = m;
                m=m*(-1); 
                bform["price"]=m;                            //price
            }
        else{
                bform["price"] = m;
                m=m*(-1); 
                sform["price"]=m;                            //price
            }
        
        

        std::vector<int> elements;
        elements.push_back(id);           //add index

        std::pair<Map<std::string,int>,std::vector<int>> mpair;
        mpair.first = bform;
        mpair.second = elements;
        int j=0;
        int prime;
        int post;
        bool flag = false;
        bool flag1 = false;
        bool flag2=false;
        for(j=0;j<order.size(); j++){
            if(mapsAreEqual(order[j].first,bform)){
                if(order[j].first["price"]<bform["price"]  && order[j].first["price"]*bform["price"] > 0 &&order[j].second.size()==1) {
                    prime= order[j].first["price"];
                    post = bform["price"];
                    // when A 1 100 b and A 1 200 b
                    flag=true;
                    break;
                }
                else if(order[j].first["price"]>bform["price"] && order[j].first["price"]*bform["price"] > 0 && order[j].second.size()==1){
                    flag1=true;
                    flag=true;
                    break;
                }
            }
            if(mapsAreEqual(order[j].first,sform) && order[j].second.size()==1 && order[j].first["price"]==sform["price"]){
                std::cout<<"No trade"<<std::endl;  // yeh A 1 100 S A 1 100 B wala case hai 
                flag2 = true;
                deleteit(order, order[j]);
            }
        }
    if(!flag2){
        order.push_back(mpair);
        if(flag1) std::cout<<"No trade"<<std::endl; // flag1 true when A 1 100 b and A 1 50 b
      

        Map<std::string,int> c;
       
        // if(order.size()==1) std::cout<<"No trade"<<std::endl;
        // else{
        if(flag){
            std::vector<std::pair<Map<std::string,int>,std::vector<int>>> wte;
            for(int k=0;k<order.size();k++){
                for(int l=0;l<order[k].second.size();l++){
                    if(order[k].second[l]==order[j].second[0]){
                         order[k].first["price"] += post-prime;
                         order[k].second.erase(order[k].second.begin() + l);
                         order[k].second.push_back(id);
                    }
                    else continue;
                }

            }
            order.erase(order.begin()+j);

           for(int f=0;f<order.size();f++){
            if(allValuesZero(order[f].first)){
                wte.push_back(order[f]);
            }
           }
           if(wte.size() ==0){
                    std::cout<<"No trade"<<std::endl;
            }
            else{
                int l;

                std::pair<Map<std::string,int>,std::vector<int>> w;
                w=findmaximum(wte,"price");
                //std::cout<<w.first.size();
                for(l = w.second.size(); l >0;l--){
                        
                    for(int i=0;i<matrix.size();i++){
                        if(matrix[i].first == w.second[l]){
                            for(int m=0;m<matrix[i].second.size();m++){
                                std::cout<<matrix[i].second[m]<<" "; 
                            }
                            std::cout<<std::endl;
                        }                    
                    }
                }
                deleteit(order,w);
                for(int m=0;m<w.second.size();m++){
                    for(int k=0;k<order.size();k++){
                        for(int l=0;l<order[k].second.size();l++){
                            if(order[k].second[l]==w.second[m]) {
                                // order[k].first.clear();
                                // order[k].second.clear();
                                order.erase(order.begin()+k);
                            }
                        }

                    }
                }   //std::cout<<w.first["price"];
                    p=p+w.first["price"];
                    //std::cout<<w.first["price"]<<std::endl;
                    wte.clear();
            }
           
            //push here also and delete the previous order
            
        }

        if(!flag){     
            
            std::pair<Map<std::string,int>,std::vector<int>> pair1;
            int si = order.size();
            int g;
            std::vector<std::pair<Map<std::string,int>,std::vector<int>>> wte;
            
            for(g=0;g<si-1;g++){
                Map<std::string,int> s = addmap(order[g].first, mpair.first);
                std::vector<int> e = addVectors(order[g].second, mpair.second);
                
                pair1.first = s;
                pair1.second = e;
                
                // std::pair<Map<std::string,int>,int> m;
                // m.first = s;
                // m.second = x;
                int l=0;
               
                if(allValuesZero(s) && pair1.first["price"] >0){
                    wte.push_back(pair1);     
                }
            }
            if(wte.size() ==0){
                    std::cout<<"No trade"<<std::endl;
            }
            else{
                int l;

                std::pair<Map<std::string,int>,std::vector<int>> w;
                w=findmaximum(wte,"price");
                
                for(l = w.second.size(); l >0;l--){
                        
                    for(int i=0;i<matrix.size();i++){
                        if(matrix[i].first == w.second[l]){
                            for(int m=0;m<matrix[i].second.size();m++){
                                std::cout<<matrix[i].second[m]<<" "; 
                            }
                            std::cout<<std::endl;
                        }                    
                    }
                }
                deleteit(order,w);
                for(int m=0;m<w.second.size();m++){
                    for(int k=0;k<order.size();k++){
                        for(int l=0;l<order[k].second.size();l++){
                            if(order[k].second[l]==w.second[m]) {
                                // order[k].first.clear();
                                // order[k].second.clear();
                                order.erase(order.begin()+k);
                            }
                        }

                    }
                }
                    p=p+w.first["price"];
                    //std::cout<<w.first["X"]<<w.first["Y"]<<w.first["Z"]<<std::endl;
                    //std::cout<<w.second.size();
                    wte.clear();
            }
        }
        }
        id++;
        i++;
    }
    std::cout<<p<<std::endl;
}


// std::vector<std::string> stringugh(std::string message) {
//     size_t i = 0;
//     std::vector<std::string> order;
//     std::string a = "";
//     while (i < message.length()) {
//         if (message[i] != ' ') {
//             a += message[i];
//         }
//         if ((message[i] == ' ' || message[i] == '#' || i == message.length() - 1) && a!="") {
//             order.push_back(a);
//             a = "";
//         }
//         ++i;
//     }
//     return order;
// }

void ordermatch(std::string message){
    int i = 0;
    Map<std::string,std::pair<std::string,std::string> > stockss;
    Map<std::string,std::string > bestbuy;
    Map<std::string,std::string > bestsell;
    while(message[i]!='$'){
        std::string a="";
        while(message[i]!='#'){
            a=a+message[i];
            i++;
        }
//  int k=0;
// while(a[k]!=NULL){
//     std::cout<<a[k];
//     k++;
// }

        std::vector<std::string>stock;
        stock = stringugh(a);
        auto it= stockss.find(stock[0]);
        auto it1 = bestbuy.find(stock[0]);
        auto it2 = bestsell.find(stock[0]);
        if (it == stockss.end()){

            if(stock[2]=="s") {stock[2] ="b";}
            else {stock[2] ="s";}
            stockss[stock[0]] = std::make_pair(stock[1],stock[2]);
            bestbuy[stock[0]] = "";
            bestsell[stock[0]] = "";
            std::cout<<stock[0]<<" "<<stock[1]<<" "<<stock[2]<<std::endl;
            // std::cout<<stock.size()<<" ";
           
           
        }

        else{
            // std::cout<<"bestbuy "<<bestbuy[stock[0]]<<" bestsell "<<bestsell[stock[0]]<<" "<<it->second.first<<" "<<stock[1]<<" ";
            if (stock[2] == "s"){
                if (bestbuy[stock[0]] == ""){
                    if (stock[1] == bestsell[stock[0]]){
                        bestsell[stock[0]] = "";
                        std::cout<<"No trade"<<std::endl;
                    }
                     else if (stoi(stock[1]) < stoi(it->value.first)){
                        it->value.first= stock[1];
                        it->value.second= "b";
                        std::cout<<it->key<<" "<<it->value.first<<" "<<"b"<<std::endl;
                    }
                    else{
                        bestbuy[stock[0]] = stock[1];
                        std::cout<<"No trade"<<std::endl;
                    }
                }
                else{
                    if (stoi(stock[1]) >= stoi(bestbuy[stock[0]])){
                        std::cout<<"No trade"<<std::endl;
                    }
                    else if (stock[1] == bestsell[stock[0]]){
                        bestsell[stock[0]] = "";
                        std::cout<<"No trade"<<std::endl;
                    }
                    else {
                        if (stoi(stock[1]) < stoi(it->value.first)){
                            it->value.first= stock[1];
                            it->value.second= "b";
                            bestbuy[stock[0]] = "";
                            std::cout<<it->key<<" "<<it->value.first<<" "<<"b"<<std::endl;
                        }
                        else{
                            bestbuy[stock[0]] = stock[1];
                            std::cout<<"No trade"<<std::endl;
                        }
                    }
                }
            }
            else if (stock[2] == "b"){
                if (bestsell[stock[0]] == ""){
                    if (stock[1] == bestbuy[stock[0]]){
                        bestbuy[stock[0]] = "";
                        std::cout<<"No trade"<<std::endl;
                    }
                    else if (stoi(stock[1]) > stoi(it->value.first)){
                        it->value.first= stock[1];
                        it->value.second= "s";
                        std::cout<<it->key<<" "<<it->value.first<<" "<<"s"<<std::endl;
                    }
                    else{
                        bestsell[stock[0]] = stock[1];
                        std::cout<<"No trade"<<std::endl;
                    }
                }
                else{
                    if (stoi(stock[1]) <= stoi(bestsell[stock[0]])){
                        std::cout<<"No trade"<<std::endl;
                    }
                    else if (stock[1] == bestbuy[stock[0]]){
                        bestbuy[stock[0]] = "";
                        std::cout<<"No trade"<<std::endl;
                        continue;
                    }
                    else{
                        if (stoi(stock[1]) > stoi(it->value.first)){
                            it->value.first= stock[1];
                            it->value.second= "s";
                            bestsell[stock[0]] = "";
                            std::cout<<it->key<<" "<<it->value.first<<" "<<"s"<<std::endl;
                        }
                        else{
                            bestsell[stock[0]] = stock[1];
                            std::cout<<"No trade"<<std::endl;
                        }
                    }
                }
            }
            else{
                 std::cout<<"No trade"<<std::endl;
            }
        }
        stock.pop_back();
        stock.pop_back();
        stock.pop_back();
        // stock.clear();
        i++;
    }
}

int main (int argc, char** argv) {

    if (argc >= 2) {
       
    if (strcmp(argv[1], "1") == 0) {
    std::string message="";
    bool foundDollar = false;
    Receiver rcv;  
 
       while(true) {
     message= message +rcv.readIML();
     if(message[message.size()-1]=='$')break;
   }

   std::string output="";
    for (char c : message) {
        if (c != '\r') {
            output += c;
        } else {
            // output += " ";
        }
    }
 std::cout<<output<<std::endl;
 ordermatch(output);
            
        }
        else if (strcmp(argv[1], "2") == 0) {
                std::string message="";
    bool foundDollar = false;
    Receiver rcv;  
 
       while(true) {
     message= message +rcv.readIML();
     if(message[message.size()-1]=='$')break;
   }

   std::string output="";
    for (char c : message) {
        if (c != '\r') {
            output += c;
        } else {
            // output += " ";
        }
    }
 //std::cout<<output<<std::endl;
makingpermutations(output);

        }
        else if (strcmp(argv[1], "3") == 0) {
            // part3(stock);
        }
        else if (strcmp(argv[1], "3") == 0) {
            // part3(stock);
        }
        else {
            std::cout << "Invalid argument. Please provide 1, 2, or 3." << std::endl;
        }
    } 
    else {
        std::cout << "Usage: ./your_program <1|2|3>" << std::endl;
    }


    return 0;
}