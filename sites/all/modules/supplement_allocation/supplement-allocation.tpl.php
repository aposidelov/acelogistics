<script>
    $(function() {
        $(".standard_crew").find('input').click(
                function(e){
                    e.stopPropagation();
                }
        );
        $( "#accordion" ).accordion();

    });
</script>
<div class="item-list">
    <h3><span>Supplement Allocation Page</span></h3>
</div>
<ul class="call-listing">
    <li class="call-listing-item">
        <div class="call-first-row">
            <strong>
                <span class="call-id"><?=$call_id;?></span>
                <span class="call-time"><?=$date_time;?></span>
                <span class="call-crew-count"><?=$count_crews;?></span>
                <span class="call-hours"><?=$count_hours;?></span>
            </strong>
        </div>
        <div style="padding-left: 10px; padding-right: 10px; padding-bottom: 10px; background-color: white;">
            <div class="call-second-row">
            <span class="call-status">
                <strong>Call Status: </strong><?=$job_status;?>
            </span>
            <span class="call-client">
                <strong>Client: </strong><span class="client <?=$client_warning_class;?>"><?=$client_name;?></span>
            </span>
            <span class="call-venue">
                <strong>Venue: </strong><?=$venue_name;?>
            </span>
            </div>
            <div class="call-third-row">
                <strong>Skills Required: </strong>
                <?=$supps;?>
            </div>

            <div class="th-title">
                <p class="crew_name">Crew Name</p>
                <p class="standard_crew">&nbsp;</p>
                <p class="additional_charge">Additional Charge</p>
                <p class="additional_crew_pay">Additional Crew Pay</p>
                <p class="comments">Comments</p>
                <p class="additional_hours">Additional Hours</p>
                <p class="total_crew">Total Crew</p>
                <p class="total_client">Total Client</p>
            </div>
            <div id="accordion">
                <?php
                $total_crew_charge = 0;
                $total_client_charge = 0;

                foreach($crews as $crew)
                {
                    $total_crew_charge += $crew['total_crew'];
                    $total_client_charge += $crew['total_client'];
                    ?>
                    <h3 class="head">
                        <div class="crew_name">
                            <p style="float: left;" ><?=$crew['name']?></p>

                        </div>
                        <div class="standard_crew">
                            <label for="standard_<?=$crew['uid']?>" style="border: 0;" >
                                <input id="standard_<?=$crew['uid']?>" name="standard_<?=$crew['uid']?>" type="checkbox" class="crew_check" <?php if($crew['standard_crew'] == 1) { ?> checked="checked" <?php } ?> style="width: 20px;" />Standard Crew</label>
                        </div>
                        <p class="additional_charge"><input name="additional_charge_<?=$crew['uid']?>" type="text" value="<?=$crew['additional_charge']?>" /></p>
                        <p class="additional_crew_pay"><input name="additional_crew_pay_<?=$crew['uid']?>" type="text" value="<?=$crew['additional_crew_pay']?>" /></p>
                        <p class="comments"><input name="comment_<?=$crew['uid']?>" type="text" value="<?=$crew['comment']?>" /></p>
                        <p class="additional_hours"><input name="additional_hours_<?=$crew['uid']?>" type="text" value="<?=$crew['additional_hours']?>" /></p>
                        <div class="total_crew"><p style="border: 1px solid; width: 90%;"><?=$crew['total_crew'];?></p></div>
                        <div class="total_client"><p style="border: 1px solid; width: 90%;"><?=$crew['total_client'];?></p></div>
                    </h3>
                    <div>
                        <?php //var_dump($variables); ?>
                        <?php
                        if(empty($crew['supplements']))
                        {
                            echo "<div class='th_columns' style='padding-top: 60px;'>"."There is no supplements for this crew."."</div>";

                            ?>

                            <div class="th_columns">
                                <p>Super Supplements</p>
                            </div>
                            <div class="tr_contents">
                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="fine_<?=$crew['uid']?>">
                                            <input id="fine_<?=$crew['uid']?>" name="fine_<?=$crew['uid']?>" type="checkbox" class="fine_check" <?php if($crew['fine'] != 0) { ?> checked="checked" <?php } ?> />Fine
                                        </label>
                                    </div>
                                    <input id="fine_amount_<?=$crew['uid']?>" name="fine_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['fine'] != 0) { ?> value="<?php echo $crew['fine']; ?>" <?php } ?> />
                                    <input class="fine_desc" id="fine_desc_<?=$crew['uid']?>" name="fine_desc_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['fine_desc']) { ?> value="<?php echo $crew['fine_desc']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="no_show_<?=$crew['uid']?>">
                                            <input id="no_show_<?=$crew['uid']?>" name="no_show_<?=$crew['uid']?>" type="checkbox" class="no_show_check" <?php if($crew['no_show'] != 0) { ?> checked="checked" <?php } ?> />no_show
                                        </label>
                                    </div>
                                    <input id="no_show_amount_<?=$crew['uid']?>" name="no_show_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['no_show'] != 0) { ?> value="<?php echo $crew['no_show']; ?>" <?php } ?> />
                                    <input class="no_show_desc" id="no_show_desc_<?=$crew['uid']?>" name="no_show_desc_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['no_show_desc']) { ?> value="<?php echo $crew['no_show_desc']; ?>" <?php } ?> />
                                </div>

                            </div>

                            <div class="th_columns">
                                <p>Total Change</p>
                            </div>
                            <div class="tr_contents">

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="crew_total_add_<?=$crew['uid']?>">
                                            <input id="crew_total_add_<?=$crew['uid']?>" name="crew_total_add_<?=$crew['uid']?>" type="checkbox" class="crew_total_add_check" <?php if($crew['crew_total_add'] != 0) { ?> checked="checked" <?php } ?> />Crew Total Add
                                        </label>
                                    </div>

                                    <input id="crew_total_add_amount_<?=$crew['uid']?>" name="crew_total_add_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['crew_total_add'] != 0) { ?> value="<?php echo $crew['crew_total_add']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="crew_total_reduce_<?=$crew['uid']?>">
                                            <input id="crew_total_reduce_<?=$crew['uid']?>" name="crew_total_reduce_<?=$crew['uid']?>" type="checkbox" class="crew_total_reduce_check" <?php if($crew['crew_total_reduce'] != 0) { ?> checked="checked" <?php } ?> />Crew Total Reduce
                                        </label>
                                    </div>

                                    <input id="crew_total_reduce_amount_<?=$crew['uid']?>" name="crew_total_reduce_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['crew_total_reduce'] != 0) { ?> value="<?php echo $crew['crew_total_reduce']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="client_total_add_<?=$crew['uid']?>">
                                            <input id="client_total_add_<?=$crew['uid']?>" name="client_total_add_<?=$crew['uid']?>" type="checkbox" class="client_total_add_check" <?php if($crew['client_total_add'] != 0) { ?> checked="checked" <?php } ?> />Client Total Add
                                        </label>
                                    </div>

                                    <input id="client_total_add_amount_<?=$crew['uid']?>" name="client_total_add_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['client_total_add'] != 0) { ?> value="<?php echo $crew['client_total_add']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="client_total_reduce_<?=$crew['uid']?>">
                                            <input id="client_total_reduce_<?=$crew['uid']?>" name="client_total_reduce_<?=$crew['uid']?>" type="checkbox" class="crew_total_reduce_check" <?php if($crew['client_total_reduce'] != 0) { ?> checked="checked" <?php } ?> />Client Total Reduce
                                        </label>
                                    </div>

                                    <input id="client_total_reduce_amount_<?=$crew['uid']?>" name="client_total_reduce_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['client_total_reduce'] != 0) { ?> value="<?php echo $crew['client_total_reduce']; ?>" <?php } ?> />
                                </div>

                            </div>

                            <?php

                        }
                        else{

                            ?>
                            <div class="th_columns">
                                <div class="th_crew">
                                    <p style="height: 50%">CREW</p>
                                    <p style="float: left; width: 50%">PH</p>
                                    <p>OF</p>
                                </div>
                                <div class="th_client">
                                    <p style="height: 50%">CLIENT</p>
                                    <p style="float: left; width: 50%">PH</p>
                                    <p>OF</p>
                                </div>
                                <div class="th_comments">
                                    <p>COMMENTS</p>
                                </div>
                            </div>
                            <div class="tr_contents">
                                <?php
                                foreach($crew['supplements'] as $supplement)
                                {
                                    ?>
                                    <div class = "crew_record">
                                        <div class="tr_crew">
                                            <label for="supp_use_<?=$crew['uid'].'_'.$supplement['nid']?>">
                                                <input id="supp_use_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_use_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_check" type="checkbox" <?php
                                                    if($supplement['checked'] == 1) {?> checked="checked" <?php } ?>/>
                                                <?=$supplement['title'];?></label></div>
                                        <?php
                                        if($supplement['crew_ph'] != NULL || $supplement['crew_of'] != NULL)
                                        {
                                            $crew_ph = $supplement['crew_ph'];
                                            $crew_of = $supplement['crew_of'];
                                        }
                                        else
                                        {
                                            $crew_ph = $variables['supp_default'][$supplement['nid']]['crew_hour'];
                                            $crew_of = $variables['supp_default'][$supplement['nid']]['crew_single'];
                                        }
                                        ?>
                                        <input id="supp_crew_ph_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_crew_ph_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_crew_ph" type="text" value="<?php echo $crew_ph;?>"/>
                                        <input id="supp_crew_of_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_crew_of_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_crew_of" type="text" value="<?php echo $crew_of;?>"/>

                                        <?php
                                        if($supplement['client_ph'] != NULL || $supplement['client_of'] != NULL)
                                        {
                                            $client_ph = $supplement['client_ph'];
                                            $client_of = $supplement['client_of'];
                                        }
                                        else
                                        {
                                            $client_ph = $variables['supp_default'][$supplement['nid']]['client_hour'];
                                            $client_of = $variables['supp_default'][$supplement['nid']]['client_single'];
                                        }
                                        ?>
                                        <input id="supp_client_ph_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_client_ph_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_client_ph"type="text" value="<?php echo $client_ph; ?>"/>
                                        <input id="supp_client_of_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_client_of_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_client_of" type="text" value="<?php echo $client_of; ?>"/>

                                        <input id="supp_comment_<?=$crew['uid'].'_'.$supplement['nid']?>" name="supp_comment_<?=$crew['uid'].'_'.$supplement['nid']?>" class="tr_comments" type="text" value="<?=$supplement['comment']?>"/>
                                    </div>
                                    <?php
                                }
                                ?>

                            </div>
                            <div class="th_columns">
                                <p>Super Supplements</p>
                            </div>
                            <div class="tr_contents">
                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="fine_<?=$crew['uid']?>">
                                            <input id="fine_<?=$crew['uid']?>" name="fine_<?=$crew['uid']?>" type="checkbox" class="fine_check" <?php if($crew['fine'] != 0) { ?> checked="checked" <?php } ?> />Fine
                                        </label>
                                    </div>
                                    <input id="fine_amount_<?=$crew['uid']?>" name="fine_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['fine'] != 0) { ?> value="<?php echo $crew['fine']; ?>" <?php } ?> />
                                    <input class="fine_desc" id="fine_desc_<?=$crew['uid']?>" name="fine_desc_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['fine_desc']) { ?> value="<?php echo $crew['fine_desc']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="no_show_<?=$crew['uid']?>">
                                            <input id="no_show_<?=$crew['uid']?>" name="no_show_<?=$crew['uid']?>" type="checkbox" class="no_show_check" <?php if($crew['no_show'] != 0) { ?> checked="checked" <?php } ?> />no_show
                                        </label>
                                    </div>
                                    <input id="no_show_amount_<?=$crew['uid']?>" name="no_show_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['no_show'] != 0) { ?> value="<?php echo $crew['no_show']; ?>" <?php } ?> />
                                    <input class="no_show_desc" id="no_show_desc_<?=$crew['uid']?>" name="no_show_desc_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['no_show_desc']) { ?> value="<?php echo $crew['no_show_desc']; ?>" <?php } ?> />
                                </div>

                            </div>

                            <div class="th_columns">
                                <p>Total Change</p>
                            </div>
                            <div class="tr_contents">

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="crew_total_add_<?=$crew['uid']?>">
                                            <input id="crew_total_add_<?=$crew['uid']?>" name="crew_total_add_<?=$crew['uid']?>" type="checkbox" class="crew_total_add_check" <?php if($crew['crew_total_add'] != 0) { ?> checked="checked" <?php } ?> />Crew Total Add
                                        </label>
                                    </div>

                                    <input id="crew_total_add_amount_<?=$crew['uid']?>" name="crew_total_add_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['crew_total_add'] != 0) { ?> value="<?php echo $crew['crew_total_add']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="crew_total_reduce_<?=$crew['uid']?>">
                                            <input id="crew_total_reduce_<?=$crew['uid']?>" name="crew_total_reduce_<?=$crew['uid']?>" type="checkbox" class="crew_total_reduce_check" <?php if($crew['crew_total_reduce'] != 0) { ?> checked="checked" <?php } ?> />Crew Total Reduce
                                        </label>
                                    </div>

                                    <input id="crew_total_reduce_amount_<?=$crew['uid']?>" name="crew_total_reduce_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['crew_total_reduce'] != 0) { ?> value="<?php echo $crew['crew_total_reduce']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="client_total_add_<?=$crew['uid']?>">
                                            <input id="client_total_add_<?=$crew['uid']?>" name="client_total_add_<?=$crew['uid']?>" type="checkbox" class="client_total_add_check" <?php if($crew['client_total_add'] != 0) { ?> checked="checked" <?php } ?> />Client Total Add
                                        </label>
                                    </div>

                                    <input id="client_total_add_amount_<?=$crew['uid']?>" name="client_total_add_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['client_total_add'] != 0) { ?> value="<?php echo $crew['client_total_add']; ?>" <?php } ?> />
                                </div>

                                <div class="crew_record">
                                    <div class="tr_crew">
                                        <label for="client_total_reduce_<?=$crew['uid']?>">
                                            <input id="client_total_reduce_<?=$crew['uid']?>" name="client_total_reduce_<?=$crew['uid']?>" type="checkbox" class="crew_total_reduce_check" <?php if($crew['client_total_reduce'] != 0) { ?> checked="checked" <?php } ?> />Client Total Reduce
                                        </label>
                                    </div>

                                    <input id="client_total_reduce_amount_<?=$crew['uid']?>" name="client_total_reduce_amount_<?=$crew['uid']?>" type="text" style="margin-left: 10px" <?php if($crew['client_total_reduce'] != 0) { ?> value="<?php echo $crew['client_total_reduce']; ?>" <?php } ?> />
                                </div>

                            </div>

                            <?php
                        }
                        ?>

                    </div>
                    <?php
                }
                ?>
            </div>
        </div>
    </li>
    <div style="margin-top: 20px;">
        <span style="float: left; margin-right: 50px;">Total Crew Charges: $<?= $total_crew_charge?></span>
        <span>Total Client Charges: $<?= $total_client_charge?></span>
    </div>
</ul>
