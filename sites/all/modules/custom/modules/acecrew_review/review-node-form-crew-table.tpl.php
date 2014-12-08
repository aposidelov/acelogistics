<h3 style="font-size: 17px; border-bottom: 1px solid #aaa;padding-bottom:5px;margin-bottom:5px;">Job Details</h3>
<dl>
<dt><strong>Client:</strong></dt><dd><?php print drupal_render($form['client_name']); ?></dd>
<dt><strong>Venue:</strong></dt><dd><?php print drupal_render($form['venue_name']); ?></dd>
<dt><strong>Date Range:</strong></dt><dd><?php print drupal_render($form['call_dates']); ?></dd>
</dl>

<table class="crew">
  <thead>
    <tr>
      <th style="text-align: center;">Picture</th>
      <th>Crew member</th>
      <th>Time Keeping</th>
      <th>Manner</th>
      <th>Work Ethic</th>
      <th>Work Ability</th>
      <th>Communicational Skills</th>
      <th class="comments">Additional Comments</th>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($form['rows'] as $uid => $row) : ?>
      <?php if (is_numeric($uid)) : ?>
        <tr>
          <td style="text-align: center;"><?php print drupal_render($form['rows'][$uid]['picture']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['username']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['timeKeeping']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['manner']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['workEthic']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['workAbility']); ?></td>
          <td><?php print drupal_render($form['rows'][$uid]['communicationalSkills']); ?></td>
          <td class="comments"><?php print drupal_render($form['rows'][$uid]['addComments']); ?></td>
        </tr>
      <?php endif; ?>
    <?php endforeach; ?>
  </tbody>
</table>

<?php print drupal_render($form) ?>

