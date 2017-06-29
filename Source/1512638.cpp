//  Created by VanTuan on 4/4/16.
//  Copyright © 2016 VanTuan. All rights reserved.
#include <iostream>
#include <fstream>
using namespace std;
/*
khai bao cau truc sinh vien
*/
struct Student
{
	string Code;
	string Name;
	string Faculty;
    string Year;
	string Gmail;
	string Birth;
	string Link_img;
	string Describe;
	string Hobby;
};
Student SV[1000];//khai bao phan tu gom 1000 sinh vien
int number = 0;
const int total=9;//đây chính là số biến mà ta đặt tring file html 
const string profile = "Website";//thư mục website
/*duong dan du lieu va temple html co san*/
string temple = "mydata/template.html";

/*
     ham doc file moi bien cach nhau boi dau ','
     rieng so thich la phan con lai
*/
void Read(Student SV[1000],int &number)
{
	string line;
	ifstream iFile("mydata/student.csv");
	if(iFile.is_open())
	{
		while(iFile.good())
		{
			Student a;
			getline(iFile,a.Code,',');
			getline(iFile,a.Name,',');
			getline(iFile,a.Faculty,',');
			getline(iFile,a.Year,',');
			getline(iFile,a.Birth,',');
			getline(iFile,a.Gmail,',');
			getline(iFile,a.Link_img,',');
			getline(iFile,a.Describe,',');
			getline(iFile,a.Hobby);
			getline(iFile,line);//đọc dòng vị bỏ trống trong file .csv
			SV[number] = a;//lưu các sinh viên vào mảng 
			number++;
		}
		iFile.close();
	}
}
/*đọc temple*/
void read_Temple(string temple_line[1000],int &count)
{
	
	ifstream Temple(temple);//mở temple-temple ta đã tạo nó sẵn đường dẫn
	if(Temple.is_open())
	{
		while(Temple.good())//kiểm tra file html có kết thúc chưa
		{
			getline(Temple,temple_line[count]);
			count++;//gía trị này là số dòng ta sẽ lấy nó ra khỏi hàm read_Temple();
		}
	}
	Temple.close();
}
/*hàm show sinh viên có chức năng kiểm tra thông tin sinh viên có đọc đúng chưa
Bạn có thể gọi nó ở hàm main để kiểm tra*/
void show_Student(Student SV[1000],int i)
{
	Read(SV,number);
	cout <<"MSSV: "<<SV[i].Code<<endl;
	cout <<"Name: "<<SV[i].Name<<endl;
	cout <<"Faculty: "<<SV[i].Faculty<<endl;
	cout <<"Year: "<<SV[i].Year<<endl;
	cout <<"Gmail: "<<SV[i].Gmail<<endl;
	cout <<"Birth: "<<SV[i].Birth<<endl;
	cout <<"Link: "<<SV[i].Link_img<<endl;
	cout <<"Describe: "<<SV[i].Describe<<endl;
	cout <<"Hobby: "<<SV[i].Hobby<<endl;
}
/**
 * thay đổi biến trong một hàng
 * Ex: "xin chao $name"
 * sau khi thay đổi: "xin chao tuan dep trai"
 */
void Template_ReplaceVariable(string &str, const string &from, const string &to) {
    if (from.empty())
    {
    	return;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
/*-----------------------------------------**
phan nay nam neu muon cai tien thi lay ra dung neu ko thi ko can dung toi
*/
string getHobbyString(string *hobbies, int total_hobbies) {
    string hobby_string = "";
    for (int i = 0; i < total_hobbies; ++i) {
        hobby_string += "<li>" + hobbies[i] + "</li>";
    }
    return hobby_string;
}
/*
    *viet vao file .html
    *ex: 1512638.html
    *ta se doc temple.html roi tu do chuyen qua 
    file html ta muon xuat ra trên trình duyệt
*/
void Write_Temple(string temp_line[1000],int i)
{
	int count = 0;
	/*
	    *temple_line[1000]:khai báo một mảng có 1000 sinh viên
	    *int i:thứ tự sinh viên ta cần viết vào file html
	    *int count:là số dòng trong file html ta cần viết vào
	*/
	Read(SV,number);//gọi hàm đọc sinh viên
	string filename =profile+"/"+SV[i].Code+".html";//đường dẫn của file html
	ofstream file(filename);//mở file để viết 
	read_Temple(temp_line,count);//đọc temple 
	const string from[total] = 
	{
            "$id", "$name", "$birthday", "$faculty",
            "$school_year","$gmail", "$avatar", "$info", "$hobbies"
    };
    /*
        *ở đây chúng ta khai bao hai mảng chuỗi
        *mảng chuỗi đâu tiên sẽ thay thế cho mảng chuỗi dưới đây
    */
    const string to[total]=
    {
    	    SV[i].Code,SV[i].Name,SV[i].Birth,SV[i].Faculty,SV[i].Year,SV[i].Gmail,SV[i].Link_img,SV[i].Describe,
    	    SV[i].Hobby
    };
    /*
        *viết dữ liệu vào file html
        *viết từng dòng->các dòng đó đã được thay đổi biến mà ta đặt tên nó trong temple hmtl
        *nó sẽ viết với các giá trị mà ta đọc đước từ student.csv qua các biến trong file html

    */
	for(int line = 0; line < count; line++)
	{
		/*
		    *ta sẽ ghi từng dòng
		    *trên các dòng ta sẽ đổi các biến trong dòng
		*/
		for(int pos = 0; pos < total; pos++)
        {
        	/*
        	    *thay đổi biến trên một hàng của temple html
        	*/
    	    Template_ReplaceVariable(temp_line[line],from[pos],to[pos]);
    	    /*
    	        *ex: <title>HCMUS - $name</title>
    	        thành <tilte>HCMUS -Nguyễn Văn Tuấn</tilte>
    	    */
        }
        //ghi vào file html
        //ghi dòng thứ line vào file html
		file <<temp_line[line];
		file <<"\n";
	}
	
}
/*hàm chính nơi giải quyết mọi vấn đề*/
int main()
{
	int pos;
	int n;/*số lượng sinh viên được lưu trong dữ liệu*/
	Read(SV,n);
	/* gọi hàm read này để tính số lượng sinh viên trong dữ liêu của chúng ta*/
	string temp_line[1000];
	cout <<"please enter localtion of student you wanna import to html:\n";
	cout <<"present your data has "<<n<<" student!!!!!!\n";
	cin >>pos;
	while (pos < 0 || pos >= n)
	{
		cout <<"enter again: ";
		cin >> pos;
	}
    Write_Temple(temp_line,pos);
    system("pause");
    //mục đích cuối cùng viết dữ liệu vào file html
	return 0;
}
/*source này có thể nâng cấp thêm-open source*/