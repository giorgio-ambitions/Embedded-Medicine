#include <iostream>
#include <string>
#include <vector>

// Structure to represent a simple event (e.g., file write or process execution)
struct SystemEvent {
    std::string process_name;
    std::string action; // e.g., "FILE_WRITE", "EXECVE"
    std::string target_path;
};

// Core Antivirus Detection Engine
class SimpleAntivirusEngine {
public:
    // Evaluate event against basic security rules
    void process_event(const SystemEvent& evt) {
        if (evt.action == "FILE_WRITE" && evt.target_path.find(".ransom") != std::string::npos) {
            trigger_alert("ALERT: Suspected Ransomware Activity detected!", evt);
        } else if (evt.action == "EXECVE" && evt.target_path.find("/tmp/malware") != std::string::npos) {
            trigger_alert("ALERT: Execution from untrusted directory!", evt);
        } else {
            std::cout << "[OK] Event passed: " << evt.process_name << " -> " << evt.target_path << std::endl;
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
    std::cout << "Starting Custom Security Engine..." << std::endl;
    SimpleAntivirusEngine engine;

    // Simulated event stream (In production, this comes from eBPF/Kernel)
    std::vector<SystemEvent> events = {
        {"bash", "EXECVE", "/usr/bin/ls"},
        {"unknown_proc", "FILE_WRITE", "/home/user/document.ransom"},
        {"curl", "EXECVE", "/tmp/malware"}
    };

    for (const auto& evt : events) {
        engine.process_event(evt);
    }

    return 0;
}
