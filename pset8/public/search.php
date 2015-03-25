<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $parameters = array_map('trim', explode(",", urldecode($_GET["geo"])));
    
    // trim US since all are US addresses (thanks bryanjackson)
    
    if (($index = array_search("US", $parameters)) !== false)
    {
        unset($parameters[$index]);
    }

    $sqlPreFix = "SELECT * FROM places WHERE ";
    
    for ($i = 0, $varCount = count($parameters); $i < $varCount; $i++)
    {
        if (is_numeric($parameters[$i]))
        {
            $sqlPreFix .= 'postal_code LIKE "' . htmlspecialchars($parameters[$i], ENT_QUOTES) . '%"';
        }
        else 
        {
            $sqlPreFix .= '(place_name LIKE "' . htmlspecialchars($parameters[$i], ENT_QUOTES) . '%" OR ' . 
            (strlen($parameters[$i]) <= 2 ? 'admin_code1 LIKE "' . htmlspecialchars($parameters[$i], ENT_QUOTES) . '%" OR ' : "") . 
            'admin_name1 LIKE "' . htmlspecialchars($parameters[$i], ENT_QUOTES) . '%")';
        }
        if ($i < ($varCount - 1))
        {
            $sqlPreFix .= " AND ";
        }
        
    }
    // SEARCH
    $places = query($sqlPreFix);
         
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
