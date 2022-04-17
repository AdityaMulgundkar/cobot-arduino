#define DEBUG_MODE false

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
