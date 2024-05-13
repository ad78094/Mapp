#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <utility>

using namespace std;

class scheduleItem {
private:
    string subject;
    string catalog;
    string section;
    string component;
    string session;
    int units;
    int totEnrl;
    int capEnrl;
    string instructor;

public:
    scheduleItem() : subject(""), catalog(""), section(""), component(""), session(""), units(0), totEnrl(0), capEnrl(0), instructor("") {}

    scheduleItem(string subject, string catalog, string section, string component, string session, int units, int totEnrl, int capEnrl, string instructor)
        : subject(subject), catalog(catalog), section(section), component(component), session(session), units(units), totEnrl(totEnrl), capEnrl(capEnrl), instructor(instructor) {}

    string getSubject() const { return subject; }
    string getCatalog() const { return catalog; }
    string getSection() const { return section; }
    string getComponent() const { return component; }
    string getSession() const { return session; }
    int getUnits() const { return units; }
    int getTotEnrl() const { return totEnrl; }
    int getCapEnrl() const { return capEnrl; }
    string getInstructor() const { return instructor; }

    void print() const {
        cout << subject << "\t\t" << catalog << "\t\t" << section << "\t\t" << component << "\t\t" << session << "\t\t" << units << "\t\t" << totEnrl << "\t\t" << capEnrl << "\t\t" << instructor << endl;
    }

    bool operator==(const scheduleItem& other) const {
        return subject == other.subject && catalog == other.catalog && section == other.section;
    }

    bool operator!=(const scheduleItem& other) const {
        return !(*this == other);
    }

    bool operator<(const scheduleItem& other) const {
        if (subject != other.subject) {
            return subject < other.subject;
        } else if (catalog != other.catalog) {
            return catalog < other.catalog;
        } else {
            return section < other.section;
        }
    }

    bool operator>=(const scheduleItem& other) const {
        return !(*this < other);
    }
};

class schedule {
private:
    map<string, scheduleItem> scheduleMap;

public:
    schedule() {}

    void initSchedule(ifstream& infile) {
        string line;
        getline(infile, line); // Discard the first line (column headers)

        while (getline(infile, line)) {
            stringstream ss(line);
            string subject, catalog, section, component, session, instructor;
            int units, totEnrl, capEnrl;

            getline(ss, subject, '\t');
            getline(ss, catalog, '\t');
            getline(ss, section, '\t');
            getline(ss, component, '\t');
            getline(ss, session, '\t');
            getline(ss, instructor, '\t');
            ss >> units;
            ss >> totEnrl;
            ss >> capEnrl;

            scheduleItem item(subject, catalog, section, component, session, units, totEnrl, capEnrl, instructor);
            addEntry(item);
        }

        infile.close();
    }

    void addEntry(const scheduleItem& item) {
        string key = item.getSubject() + "_" + item.getCatalog() + "_" + item.getSection();
        scheduleMap[key] = item;
    }

    void print() const {
        for (map<string, scheduleItem>::iterator it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            it->second.print();
        }
    }

    void findSubject(string subject) {
        cout << "Records with subject " << subject << ":" << endl;

        for (map<string, scheduleItem>::iterator it = scheduleMap.begin
