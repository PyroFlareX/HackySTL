#include <Json.hpp>
#include <Io.hpp>

static const char* test_filename = "Tests/Json/TestFile.json";

int main() 
{
    using namespace hsd::string_view_literals;
    setlocale(LC_ALL, "en_US.UTF-8");
    hsd::JsonStream<char> lexer;
    
    // Lex the string
    lexer.lex_file(test_filename).unwrap();
    lexer.push_eot().unwrap();

    hsd::JsonParser parser(lexer);
    // Parse the string
    auto value = parser.parse_next().unwrap();

    // Assert that the whole object is complete
    assert(value->is_complete());
    
    [[maybe_unused]] auto res = (*value)["LoS"_sv][0]["age"_sv].as_num().unwrap();
}