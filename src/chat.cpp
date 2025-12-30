    #include "chat.hpp"
    
    void Chat::addMessage(ChatMessage m){
        messages.push_back(m);
    }
    
    std::ostream& Chat::render(std::ostream& s){
        for(auto m : messages){
            s << config.authorDeco.first << m.author << config.authorDeco.second << config.authorMessageBreak << m.message << "\n";
        }
        s << "----------------------------\n";
        s << config.authorDeco.first << username << config.authorDeco.second << config.authorMessageBreak << std::flush;
        return s;
        
    }

    std::ostream& operator<<(std::ostream& s, Chat& c){
        c.render(s);
        return s;
    }