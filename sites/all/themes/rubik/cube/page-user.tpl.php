<?php
include('header.inc'); ?>

<div class='acecrew-profile-view'>
    <div id='page' class='clear-block limiter page-content acecrew-profile-view'>
        <?php if ($show_messages && $messages): ?>
        <div id='console' class='clear-block'><?php print $messages; ?></div>
        <?php endif; ?>

        <div id='content'>
            <h1 style="font-size: 20px; padding: 10px 0 0 8px"><?php echo $title; ?><?php echo print_insert_link(); ?></h1>
            <?php if (!empty($content)): ?>
            <div class='content-wrapper clear-block'><?php print $content ?></div>
            <?php endif; ?>
            <?php print $content_region ?>
        </div>
    </div>
</div>

<?php include('footer.inc'); ?>
