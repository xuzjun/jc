namespace java com.chenglun.BlockedService

service DayQuotationService {
    string  subscribeDayQuotation(string code, string startDate, string endDate);
}