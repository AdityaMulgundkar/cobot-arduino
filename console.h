#define DEBUG_MODE true

class console {

  public:
    template <typename Generic>
    void log(Generic value) {
#if defined(DEBUG_MODE) && (DEBUG_MODE == true)
      if (Serial) {
        Serial.println(value);
      }
#endif
    }

    template <typename Generic, typename Generic2>
    void log(Generic value, Generic2 value2) {
#if defined(DEBUG_MODE) && (DEBUG_MODE == true)
      if (Serial) {
        Serial.print(value);
        Serial.println(value2);
      }
#endif
    }

    void log(unsigned long value, unsigned char value2[8]) {
#if defined(DEBUG_MODE) && (DEBUG_MODE == true)
      if (Serial) {
          Serial.print(value, HEX);
          Serial.print(": ");
          for (int i = 0; i < 8; i++)
          {
            Serial.print(value2[i], HEX);
            Serial.print("  ");
          }
          Serial.println("");
      }
#endif
    }

    template <typename Generic>
    void log_without_endl(Generic value) {
#if defined(DEBUG_MODE) && (DEBUG_MODE == true)
      if (Serial) {
        Serial.print(value);
      }
#endif
    }

    template <typename Generic, typename Type>
    void log_with_type(Generic value, Type type) {
#if defined(DEBUG_MODE) && (DEBUG_MODE == true)
      if (Serial) {
        Serial.println(value, type);
      }
#endif
    }
};
