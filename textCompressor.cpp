#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;


//Tree node

struct Node{
    char ch;
    int freq;
    Node*left, *right;
};

// making the node to push into the heap

Node* getNode(char ch,int freq,Node *left,Node *right){

    Node* node = new Node();
    node->ch=ch;
    node->freq=freq;
    node->left=left;
    node->right=right;

    return node;
}

// making a comparison function for getting a minheap

struct comparison{
    bool operator()(Node* left,Node* right){
            return left->freq > right->freq;
    }
};

// code for encoding 
// traverse the huffman tree and stroe the huffman codes 
// in a map

void encode(Node *root ,string str, unordered_map<char,string> &huffmancode){

    if(root==NULL){
        return ;
    }

    // if leaf node is found
    if(!root->left && !root->right){
        huffmancode[root->ch] = str;
    }

    // now we will make the str
    // for this add "0" to str if moving left
    // and "1" if moving right

    encode(root->left,str+"0",huffmancode);
    encode(root->right,str+"1",huffmancode); 
}

// now code for decoding
// traverse the tree and decode the string

void decode(Node *root, int &index , string str){
    
    if(root==NULL){
        return;
    }

    // if leaf node is found
    if(!root->left && !root->right){
        cout<<root->ch;
        return;
    }

    index++;

    if(str[index] == '0'){
        decode(root->left,index,str);
    }
    else{
        decode(root->right, index,str);
    }
}

// creating a Huffman tree and decoding it afterwards

void HuffManTree(string file){
    // create a map
    // to store frequency of characters in the file

    unordered_map<char,int> freq;

    for(auto i:file){
        freq[i]++;
    }

    // making a priority queue for storing nodes
    // and also storing them in increasnig order

    priority_queue<Node* , vector<Node*> , comparison> pq;

    // create a node for every character and add it to the queue
    for(auto i:freq){
        pq.push(getNode(i.first,i.second,NULL,NULL));
    }


    // traverse the queue till only 1 element is left
    // that 1 element will be the root node the ie biggest parent
    // which will have the total frequency of all the elements in the file
    while(pq.size() != 1){

        // the lower frequency will be stored in the left node
        Node *left = pq.top();
        pq.pop();

        // the higher frequency will be stored in the right node
        Node *right = pq.top();
        pq.pop();


        // now we will store the sum of the frequencies in a parent node
        // and this parent node will be now pushed into the queue

        int parentsum = left->freq + right->freq;
        pq.push(getNode('\0',parentsum,left,right));
    }

    // this is the top most parent or the main root 
    // with address of the huffman tree
    Node *root = pq.top();


    // Now run the encode function 
    // and make a map to stroe the codes
    // also print the codes

    unordered_map<char,string> huffmancode;
    encode(root,"",huffmancode);

    cout<<"HUFFMAN CODES ARE : \n"<<endl;

    for(auto i:huffmancode){
        cout<<i.first<<"  "<<i.second<<endl;
    }

    // printing the original string
    cout<<"\nThe original string is : \n"<<file<<endl;

    // print the encoded string
    string str="";
    for(auto i:file){
        str+= huffmancode[i];
    }

    cout<<"\nEncoded Huffman code is : \n"<<str<<endl;

    // now decode the string
    int index=-1;
    cout<<"\nDecoded string is : \n";
    int t=str.size();
    while(index<t-1){
        decode(root,index,str);
    }
}

// driver code
int main(){
    string file="lorem ipsum #$%& )HIJKLM( 04823093) heisopfs  ,. <> ?/";

    HuffManTree(file);

    return 0;
}


/* example file : "lorem ipsum #$%& )HIJKLM( 04823093) heisopfs  ,. <> ?/"

HUFFMAN CODES ARE : 

`  11111
(  111100
?  111011
l  111010
%  111001
#  111000
M  110111
&  110110
r  110101
4  110100
p  11001
>  111101
m  11000
e  10111
o  10110
,  011110
.  011100
s  0100
3  01101
J  100100
0  01100
u  101011
i  01011
$  100110
   00
/  010100
<  010101
2  011111
I  100010
L  100000
K  100001
8  100011
f  101010
H  100101
9  011101
h  100111
)  10100

The original string is :
lorem ipsum #$%& )HIJKLM( 04823093) heisopfs  ,. <> ?/

Encoded Huffman code is :
1110101011011010110111110000001011110010100101011110000011100010011011100111011000101001001011000101001001000011000001101111111000001100110100100011011111011010110001110101101101000010011110111010110100101101100110101001000011111111111111100011110011100000101011111010011101101010000

Decoded string is :
lorem ipsum #$%& )HIJKLM( 04823093) heisopfs  ,. <> ?/     */