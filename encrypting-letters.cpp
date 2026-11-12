#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct Node 
{
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char l, int f)
    {
        data = l;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    Node(int f, Node* l, Node* r)
    {
        data = '\0';
        frequency = f;
        left = l;
        right = r;
    }
};

std::vector<std::pair<char,int>> get_frequency(std::string word);
std::string huffman_encoding(std::vector<std::pair<char,int>> &frequencyArr, std::string word);
void dfs(Node* root, std::string currentCode,std::unordered_map<char,std::string> &keycode);



int main()
{
    while(true)
    {
        std::string word;
        std::cout << "\nWord(/0 to quit): ";
        std::cin >> word;
        if(word == "/0")
        {
            break;
        }
        std::vector<std::pair<char,int>> letterFrequency = get_frequency(word);

        // for(auto _ : letterFrequency)
        // {
        //     std::cout<< _.first << ":" << _.second << std::endl;
        // }

        std::string encryptedCode = huffman_encoding(letterFrequency, word);
        std::cout<< encryptedCode;
    }

    return 0;
}

std::vector<std::pair<char, int>> get_frequency(std::string word)
{
    std::vector<std::pair<char, int>> frequencyData;
    std::vector<char> metLetter;

    for(auto i : word)
    {
        bool alrChecked = false;

        for(const auto _ : metLetter)
        {
            if(i == _)
            {
                alrChecked = true;
                break;
            }
        }

        if(alrChecked)
        {
            continue;
        }

        int c=0;
        char curLetter = i;

        for(auto j : word)
        {
            if(curLetter == j)
            {
                c++;
            }
        }
        frequencyData.push_back(std::pair<char,int>(curLetter,c));
        metLetter.push_back(curLetter);
    }

    return frequencyData;
}

std::string huffman_encoding(std::vector<std::pair<char,int>> &frequencyArr, std::string word)
{
    std::vector<Node*> nodes;
    for(auto const &p : frequencyArr)
    {
        nodes.push_back(new Node(p.first, p.second));
    }

    while(nodes.size() > 1)
    {
        //sort node
        std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b)
        {   
            return a->frequency < b->frequency;
        });

        //get left and right node
        Node* leftNode = nodes[0];
        Node* rightNode = nodes[1];

        int sumFreq = leftNode->frequency + rightNode->frequency;
        Node* parent = new Node(sumFreq, leftNode, rightNode);

        nodes.erase(nodes.begin(), nodes.begin()+2);
        nodes.push_back(parent);
    }

    Node* root = nodes[0];
    std::unordered_map<char,std::string> keycode;
    dfs(root,"",keycode);
    std::string encodedString = "";
    for(int w = 0; w < word.size(); w++)
    {
        encodedString+= keycode[word[w]];
    }

    return encodedString;

}

void dfs(Node* root, std::string currentCode, std::unordered_map<char,std::string> &keycode)
{
    if(root == nullptr) return;

    if(root->left == nullptr && root->right == nullptr)
    {
        keycode[root->data] = currentCode;
        return;
    }

    dfs(root->left, currentCode+"0", keycode);
    dfs(root->right, currentCode+"1",keycode);
}
