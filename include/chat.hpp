#include <string>
#include <vector>
#include <ostream>

struct ChatMessage {
    std::string message;
    std::string author;
};

struct ChatConfig {
    std::pair<char, char> authorDeco = {'[', ']'};
    char authorMessageBreak = ':';
    int maxRenderedMessages = 40;
};

class Chat {
    std::vector<ChatMessage> messages;
    ChatConfig config;
public:
    std::string username;
    void addMessage(ChatMessage m);
    std::ostream& render(std::ostream& s);
};

std::ostream& operator<<(std::ostream& s, Chat& c);