/* Define the types of nodes in the AST and the fields associated with each
node. Defining a name and it's types results in creation of a POD struct that
consumes its arguments and a factory function to make an instance of the
Expr type. Example follows:

DefineWithOneField(ExampleExpression, string, foo) ->

struct ExampleExpression {
    string foo;
    ExampleExpression(string foo) : foo(std::move(foo)) {}
};

intline Expr MakeExampleExpression(string&& foo) {
    return std::make_unique<ExampleExpression>(std::move(foo));
}
*/
#define DefineWithOneField(TYPE, NAME, FIELD1_TYPE, FIELD1_NAME)               \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME) : FIELD1_NAME(std::move(FIELD1_NAME)) {} \
    };                                                                         \
    inline TYPE Make##NAME(FIELD1_TYPE&& FIELD1_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME));                 \
    }

#define DefineWithTwoFields(TYPE, NAME, FIELD1_TYPE, FIELD1_NAME, FIELD2_TYPE, \
                            FIELD2_NAME)                                       \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        FIELD2_TYPE FIELD2_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME, FIELD2_TYPE FIELD2_NAME)                 \
            : FIELD1_NAME(std::move(FIELD1_NAME)),                             \
              FIELD2_NAME(std::move(FIELD2_NAME)) {}                           \
    };                                                                         \
    inline TYPE Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                          \
                           FIELD2_TYPE&& FIELD2_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME),                  \
                                      std::move(FIELD2_NAME));                 \
    }

#define DefineWithThreeFields(TYPE, NAME, FIELD1_TYPE, FIELD1_NAME,            \
                              FIELD2_TYPE, FIELD2_NAME, FIELD3_TYPE,           \
                              FIELD3_NAME)                                     \
    struct NAME {                                                              \
        FIELD1_TYPE FIELD1_NAME;                                               \
        FIELD2_TYPE FIELD2_NAME;                                               \
        FIELD3_TYPE FIELD3_NAME;                                               \
        NAME(FIELD1_TYPE FIELD1_NAME, FIELD2_TYPE FIELD2_NAME,                 \
             FIELD3_TYPE FIELD3_NAME)                                          \
            : FIELD1_NAME(std::move(FIELD1_NAME)),                             \
              FIELD2_NAME(std::move(FIELD2_NAME)),                             \
              FIELD3_NAME(std::move(FIELD3_NAME)) {}                           \
    };                                                                         \
    inline TYPE Make##NAME(FIELD1_TYPE&& FIELD1_NAME,                          \
                           FIELD2_TYPE&& FIELD2_NAME,                          \
                           FIELD3_TYPE&& FIELD3_NAME) {                        \
        return std::make_unique<NAME>(std::move(FIELD1_NAME),                  \
                                      std::move(FIELD2_NAME),                  \
                                      std::move(FIELD3_NAME));                 \
    }