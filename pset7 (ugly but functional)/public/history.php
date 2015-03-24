<?php

    // get information 
    require("../includes/config.php"); 
    $history = query("SELECT symbol, shares, timestamp, action, id FROM history WHERE id = ?", $_SESSION["id"]);
    
    
    
            
    $positions = [];
    // apply information to array to be passed to portfolio
    foreach ($history as $row)
    {
        
        $positions[] = [
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "timestamp" => $row["timestamp"],
                "action" => $row["action"],
                "id" => $_SESSION["id"]
                ];
     }
    

    // render portfolio
    render("history_form.php", ["positions" => $positions, "title" => "History"]);

?>
