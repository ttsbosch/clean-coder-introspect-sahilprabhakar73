#include "TradeProcessor.h"

void TradeProcessor::processTrades(std::istream& input_file)
{

    std::vector<std::string> trade_entries;
    std::string trade;
    while (std::getline(input_file, trade))
    {
        trade_entries.push_back(trade);
    }

    std::vector<TradeRecord> trade_records;
    int lineCount = 1;
    for (const auto& item : trade_entries)
    {
        std::vector<std::string> fields;

        std::string trade_item;
        std::istringstream tStream(item);
        while (std::getline(tStream, trade_item, ','))
        {
            fields.push_back(trade_item);
        }
        if (fields.size() != 3)
        {
            std::cout << "WARN: Line " << lineCount << " malformed. Only " << fields.size() << " field(s) found." << std::endl;
            continue;
        }
        if (fields[0].length() != 6)
        {
            std::cout << "WARN: Trade currencies on line " << lineCount << " malformed: '" << fields[0] << "'" << std::endl;
            continue;
        }
        int trade_amount;
        if (!TradeDataConversion::parseIntFromString(fields[1], trade_amount))
        {
            std::cout << "WARN: Trade amount on line " << lineCount << " not a valid integer: '" << fields[1] << "'" << std::endl;
        }
        double trade_price;
        if (!TradeDataConversion::parseDoubleFromString(fields[2], trade_price))
        {
            std::cout << "WARN: Trade price on line " << lineCount << " not a valid decimal: '" << fields[2] << "'" << std::endl;
        }
        
        std::string source_currency = fields[0].substr(0, 3);
        std::string destination_currency = fields[0].substr(3, 3);
        // calculate values
        TradeRecord  trade_record;
        trade_record.sourceCurrency = source_currency;
        trade_record.destinationCurrency = destination_currency;
        trade_record.lots = trade_amount / lot_size;
        trade_record.price = trade_price;
        trade_records.push_back(trade_record);
        lineCount++;
    }

    xml_generator.generateXml(trade_records);

}


int main()
{
    TradeProcessor processor;
    std::ifstream input_file("trades.txt");
    if (input_file.is_open())
    {
        processor.processTrades(input_file);
        input_file.close();
    }
    else
    {
        std::cout << "Failed to open file" << std::endl;
    }
    return 0;
}
