#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct TradeRecord
{
    std::string sourceCurrency;
    std::string destinationCurrency;
    float lots;
    double price;
};

class XmlGenerator{
public:
    void generateXml(const std::vector<TradeRecord>& trade_records)
    {  
        std::ostringstream xmlStream;
        xmlStream << "<TradeRecords>" << std::endl;
        for (const auto& record : trade_records) {
            xmlStream << "\t<TradeRecord>" << std::endl;
            xmlStream << "\t\t<SourceCurrency>" << record.sourceCurrency << "</SourceCurrency>" << std::endl;
            xmlStream << "\t\t<DestinationCurrency>" << record.destinationCurrency << "</DestinationCurrency>" << std::endl;
            xmlStream << "\t\t<Lots>" << record.lots << "</Lots>" << std::endl;
            xmlStream << "\t\t<Price>" << record.price << "</Price>" << std::endl;
            xmlStream << "\t</TradeRecord>" << std::endl;
        }
        xmlStream << "</TradeRecords>";
        std::string xmlData = xmlStream.str();
        std::ofstream outFile("output.xml"); // Output XML file
        outFile << xmlData;
        std::cout << "INFO: " << trade_records.size() << " trades processed" << std::endl;
    }
}; 


class TradeProcessor
{
public:
    void processTrades(std::istream& stream);
    
private:
    static constexpr float lot_size{100000}; 
    XmlGenerator xml_generator;    
};

class TradeDataConversion
{
public:
    static bool parseIntFromString(const std::string& str, int& value)
    {
        try
        {
            value = std::stoi(str);
            return true;
        }
        catch (const std::exception& error)
        {
            std::cout << "Failed to parse integer from string: " << error.what() << std::endl;
            return false;
        }
    }

    static bool parseDoubleFromString(const std::string& str, double& value)
    {
        try
        {
            value = std::stod(str);
            return true;
        }
        catch (const std::exception& error)
        {   
            std::cout << "Failed to parse double from string: " << error.what() << std::endl;
            return false;
        }
    }
};



// int main()
// {
//     TradeProcessor processor;
//     std::ifstream file("trades.txt");
//     if (file.is_open())
//     {
//         processor.ProcessTrades(file);
//         file.close();
//     }
//     else
//     {
//         std::cout << "Failed to open file" << std::endl;
//     }
//     return 0;
// }

