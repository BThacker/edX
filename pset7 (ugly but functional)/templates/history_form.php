<div>
    </br>
    <a href="index.php">BACK</a> 
    </br>
<?php foreach ($positions as $position): ?>
    <tr>
        <td><?=$position["symbol"] ?></td>
        <td><?=$position["shares"] ?></td>
        <td><?=$position["action"] ?></td>
        <td><?=$position["timestamp"] ?></td>
        
    </tr>
    </br>
<?php endforeach ?>
<?php
    
  
?>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
