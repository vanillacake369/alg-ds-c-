#include <iostream>     // input&output stream :: cout, cin ...
#include <algorithm>    // algorithm :: sort(),merge(),union() ...
#include <sstream>      // string stream :: stringstream(자료형이 한 줄에 들어오면 파싱)

// start class :: dynamic_array
template <typename T>
class dynamic_array
{
    T* data;
    size_t n;

public:
    // 생성자 : 길이지정
    dynamic_array(int n)
    {
        this->n = n;
        data = new T[n];
    }

    // 복사생성자
    dynamic_array(const dynamic_array<T>& other)
    {
        n = other.n;
        data = new T[n];

        for (int i = 0; i < n; i++)
            data[i] = other[i];
    }

    // 접근자 재정의
    T& operator[](int index)
    {
        return data[index];
    }
    const T& operator[](int index) const
    {
        return data[index];
    }

    // at() 재정의
    T& at(int index)
    {
        if (index < n)
            return data[index];
        throw "Index out of range";
    }

    // 배열 크기 반환
    size_t size() const
    {
        return n;
    }

    // 소멸자 정의
    ~dynamic_array()
    {
        delete[] data; // 메모리 릭 방지
    }

    // 현재 가르키고 있는 index의 위치 반환 : 일반멤버함수 & 상수멤버함수
    T* begin() { return data; }
    const T* begin() const { return data; }
    // 마지막 index의 위치 반환 : 일반멤버함수 & 상수멤버함수
    T* end() { return data + n; }
    const T* end() const { return data + n; }

    // 깊은 복사 함수
    friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
    {
        // result라는 동적배열타입객체 생성 (길이는 arr1,arr2의 길이 합한 것)
        dynamic_array<T> result(arr1.size() + arr2.size());
        // arr1의 첫번째부터 마지막 원소까지 result.begin()의 위치부터 차례로 copy
        std::copy(arr1.begin(), arr1.end(), result.begin());
        // arr2의 첫번째부터 마지막 원소까지 result.begin()+arr1.size()의 위치부터 차례로 copy
        std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

        return result;
    }

    // 배열에 저장된 모든 데이터를 문자열로 반환함수
    std::string to_string(const std::string& sep = ", ")
    {
        // 배열길이가 0이라면 데이터가 없으므로 ""반환
        if(n==0)
            return "";

        // 문자열 파싱을 위해 ostringstream 객체 사용
        std::ostringstream os;
        // 첫 데이터 파싱
        os << data[0];
        // "," 구분자로 나머지 모든 데이터 파싱
        for(int i=1;i<n;i++)
            os << sep << data[i];

        // 파싱된 문자열 반환
        return os.str();
    }
}; // end class :: dynamic_array

// 학생 정보를 저장한 구조체 student 정의
struct student
{
    std::string name;
    int standard;
};
// 학생 정보 모두 출력(<<연산자 재정의)
std::ostream& operator<<(std::ostream& os, const student& s)
{
    return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
    // 학생 수
    int nStudents;
    std::cout << "1반 학생 수를 입력하세요: ";
    std::cin >> nStudents;

    // (학생들 저장할) 배열 정의
    dynamic_array<student> class1(nStudents);
    // 배열의 각 학생들 데이터 입력
    for (int i = 0; i < nStudents; i++)
    {
        std::string name;
        int standard;
        std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
        std::cin >> name >> standard;
        class1[i] = student{name, standard};
    }

    // 배열 크기보다 큰 인덱스의 학생에 접근
    try
    {
        // 아래 주석을 해제하면 프로그램이 비정상 종료합니다.
        // class1[nStudents] = student {"John", 8}; // 예상할 수 없는 동작

        class1.at(nStudents) = student{"John", 8}; // 예외 발생
    }
    catch (...)
    {
        std::cout << "예외 발생!" << std::endl;
    }

    // 깊은 복사
    auto class2 = class1;
    std::cout << "1반을 복사하여 2반 생성: " << class2.to_string() << std::endl;

    // 두 학급을 합쳐서 새로운 큰 학급을 생성
    auto class3 = class1 + class2;
    std::cout << "1반과 2반을 합쳐 3반 생성 : " << class3.to_string() << std::endl;

    return 0;
}