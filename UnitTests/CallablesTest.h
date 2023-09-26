bool stringToBoolSuccess = false;

bool stringToBool(String str)
{
    str.toLowerCase();
    return (str == "true" ? true : false);
}

void testCallables()
{
    auto& strToBoolFunc = invokable_get(stringToBool);
    if (strToBoolFunc)
        stringToBoolSuccess = strToBoolFunc("TrUe");
}

bool testCallablesEnd()
{
    return stringToBoolSuccess;
}