#include <iostream>
#include <string>
#include <vector>

// Structure to represent a system event
struct SystemEvent {
    std::string process_name;
    std::string action; // e.g., "FILE_WRITE", "EXECVE"
    std::string target_path;
};

// Structure to represent a dynamic security rule
struct SecurityRule {
    std::string rule_name;
    std::string required_action;
    std::string path_substring;
    std::string alert_message;
};

// Core Antivirus Detection Engine
class SimpleAntivirusEngine {
private:
    std::vector<SecurityRule> rules;

public:
    // Dynamically add rules to the engine
    void add_rule(const SecurityRule& rule) {
        rules.push_back(rule);
    }

    // Evaluate incoming events against all loaded rules
    void process_event(const SystemEvent& evt) {
        bool matched = false;

        for (const auto& rule : rules) {
            if (evt.action == rule.required_action && 
                evt.target_path.find(rule.path_substring) != std::string::npos) {
                trigger_alert(rule.alert_message, evt);
                matched = true;
                break;
            }
        }

        if (!matched) {
            std::cout << "[OK] Event passed safely: " << evt.process_name << " -> " << evt.target_path << std::endl;
        }
    }

private:
    void trigger_alert(const std::string& message, const SystemEvent& evt) {
        std::cout << "\033[1;31m[!] " << message << "\033[0m\n"
                  << "    Process: " << evt.process_name << "\n"
                  << "    Action:  " << evt.action << "\n"
                  << "    Target:  " << evt.target_path << "\n" << std::endl;
    }
};

int main() {
    std::cout << "Starting Dynamic Security Engine..." << std::endl;
    SimpleAntivirusEngine engine;

    // Load rules dynamically into memory
    engine.add_rule({"Ransomware Detector", "FILE_WRITE", ".ransom", "ALERT: Suspected Ransomware Activity detected!"});
    engine.add_rule({"Malware Execution", "EXECVE", "/tmp/malware", "ALERT: Execution from untrusted directory!"});
    engine.add_rule({"Password Access", "FILE_WRITE", "/etc/passwd", "ALERT: Unauthorized modification of sensitive files!"});

    // Simulated event stream
    std::vector<SystemEvent> events = {
        {"bash", "EXECVE", "/usr/bin/ls"},
        {"unknown_proc", "FILE_WRITE", "/home/user/document.ransom"},
        {"curl", "EXECVE", "/tmp/malware"},
        {"malicious_script", "FILE_WRITE", "/etc/passwd"}
    };

    for (const auto& evt : events) {
        engine.process_event(evt);
    }

    return 0;
}
