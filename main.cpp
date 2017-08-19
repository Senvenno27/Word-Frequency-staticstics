#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#define lineMaxWord 200

struct Record
{
	std::string word;
	int freq;
};

class WordStatic
{
public:
	//1,传引用，减少开销 2.const修饰，防止修改
	void read_file(const std::string & filename);
	void write_file(const std::string &  filename);
private:
	std::vector<Record> vec;
};

void WordStatic::read_file(const std::string &filename)
{
	//逐行读取，将行读入字符串
	std::ifstream ifs(filename.c_str());
	std::string str;
	
	if(ifs.good() == 0)
	{
		std::cout << "open readfile failed" << std::endl;
		return;
	}
	int count = 10000;
	while(getline(ifs,str) && count--)
	{
		std::stringstream ss(str);
		std::string word;
		while(ss >> word)
		{
			//std::cout<< word << std::endl;
			std::vector<Record>::iterator it;
			for(it = vec.begin(); it !=vec.end(); ++it)
			{
				//string 重载了等号
				if(word == (*it).word)
				{
					(*it).freq +=1;
					break;
				}
			}
			if(it == vec.end())
			{
				Record newRe;
				newRe.word = word;
				newRe.freq = 1;
				vec.push_back(newRe);
			}
		}
	}
	ifs.close();
}

void WordStatic::write_file(const std::string & filename)
{
	//从流中写数据
	std::vector<Record>::iterator it;
	std::ofstream ofs(filename);
	if(ofs.good() == 0)
	{
		std::cout << "open write_file failed" << std::endl;
	}
	for(it = vec.begin(); it != vec.end(); ++it)
	{
		ofs << (*it).word << " " << (*it).freq << std::endl;
		//std::cout << (*it).word << " " << (*it).freq << std::endl;
	}
	ofs.close();
}
int main(void)
{
	WordStatic wd;
	wd.read_file("The_Holy_Bible.txt");
	wd.write_file("statics.txt");

	return 0;
}
