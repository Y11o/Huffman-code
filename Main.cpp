#include "Map.cpp"
#include <queue>
using namespace std;

struct containerForTest 
{
	string encodedText;
	string decodedText;
};

int sizeCounter = 0;
containerForTest test;

struct Node		//tree node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)	//function to allocate a new tree node
{
	Node* node = new Node();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;		//highest priority elem has lowest frequency
	}
};

void encode(Node* root, string str,				//traverse the Huffman Tree and store Huffman Codes in a map
			Map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {			// found a leaf node
		sizeCounter += str.size();
		str += ' ';
		huffmanCode.insert(root->ch, str);
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)		//traverse the Huffman Tree and decode the encoded string
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)		//found a leaf node
	{
		cout << root->ch;
		test.decodedText += root->ch;
		return;
	}

	index++;
	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)		//builds Huffman Tree and decode given input text
{
	Map<char, int> freq;				//count frequency of appearance of each char and store it in a map
	for (char ch: text) {
		if (freq.find(ch) == nullptr)
		{
			freq.insert(ch, 0);
		}
		freq.find(ch)->value++;
	}
	priority_queue<Node*, vector<Node*>, comp> pq;			//create a priority queue to store live nodes of Huffman tree

	List<char> keys = *freq.get_keys();			//create a leaf node for each character and add it to the priority queue
	List<int> values = *freq.get_values();
	for (int i = 0; i < keys.get_size(); i++) {
		pq.push(getNode(keys.at(i), values.at(i), nullptr, nullptr));
	}

	while (pq.size() != 1)		//do till there is more than one node in the queue
	{
		Node *left = pq.top(); pq.pop();		//remove the two nodes of highest priority (lowest frequency) from the queue
		Node *right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;				//create a new internal node with these two nodes as children and with frequency equal to the sum
		pq.push(getNode('\0', sum, left, right));		//of the two nodes' frequencies. Add the new node to the priority queue
	}
	Node* root = pq.top();		// root stores pointer to root of Huffman Tree

	Map<char, string> huffmanCode;		// traverse the Huffman Tree and store Huffman Codes in a map. Also prints them
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << endl;
	List <int> freqValues = *freq.get_values();
	List<char> hCodeKeys = *huffmanCode.get_keys();
	List<string> hCodeValues = *huffmanCode.get_values();
	for (int i = 0; i < hCodeKeys.get_size(); i++) {
		cout << "Char: " << hCodeKeys.at(i) << " Frequency: " << freqValues.at(i) << " Huffman code: " << hCodeValues.at(i) << endl;
	}

	cout << "\nOriginal string was :\n" << text << endl;
	cout << "\nSize of original string is :\n" << text.size() * 8 << endl;

	string str = "";
	for (char ch: text) {
		string add = huffmanCode.find(ch)->value;
		str += add;
	}
		
	cout << "\nEncoded string is :\n" << str << endl;		//print encoded string
	test.encodedText = str;
	cout << "\nSize of encoded string is :\n" << sizeCounter << endl;

	int index = 0;						//traverse the Huffman Tree again and this time decode the encoded string
	cout << "\nDecoded string is: \n";
	for (index; index <= (int)str.size() - 2; index++)
	{
		string subString = "";
		do
		{
			subString += str[index];
			index++;
		} while (str[index] != ' ');
		int iter = 0;
		while (iter <= (int)subString.size() - 2) {
			decode(root, (--iter), subString);
		}
	}
	cout << endl;

	cout << "\nCompression ratio is: \n" << text.size() * 8 / sizeCounter << endl;
}

int main()
{
	string text;

	cout << "\nInput text to encode..\n";

	getline(cin, text);

	buildHuffmanTree(text);

	return 0;
}