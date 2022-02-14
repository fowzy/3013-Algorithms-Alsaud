    for (int i = 0; i < array.Size(); i++) { // loop through array
        found = array[i].find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
            matches.Insert(array[i]);     // add to matches
        }
    }