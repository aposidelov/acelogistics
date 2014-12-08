<?php
// $Id: node.tpl.php,v 1.4 2007/08/07 08:39:36 goba Exp $
?>

<?php if ($is_front != ""){ ?>
    <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?> node-column">
        <?php if ($page == 0): ?>
            <?php print $picture ?>
            <h1 class="title"><a href="<?php print $node_url ?>"><?php print $title ?></a></h1>
            <div class="submit"><span class="submitted"><?php print $submitted ?></span></div>
        <?php endif; ?>
        <div class="taxonomy"><?php print $terms ?></div>
      
        <div class="content">
            <?php print $content ?>
        </div>
    
        <?php if ($links): ?>
            <div class="links-indent">
                <div class="links"><?php print $links ?></div>
            </div>
            <div class="clear"></div>
        <?php endif; ?>
    </div>
<?php }else{ ?>
    <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
        <?php if ($page == 0): ?>
            <?php print $picture ?>
            <h1 class="title"><a href="<?php print $node_url ?>"><?php print $title ?></a></h1>
            <div class="submit"><span class="submitted"><?php print $submitted ?></span></div>
        <?php endif; ?>
        <div class="taxonomy"><?php print $terms ?></div>
      
        <div class="content">
            <?php print $content ?>
        </div>
    
        <?php if ($links): ?>
            <div class="links-indent">
                <div class="links"><?php print $links ?></div>
            </div>
            <div class="clear"></div>
        <?php endif; ?>
    </div>
<?php } ?>