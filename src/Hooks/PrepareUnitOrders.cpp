#include "Hooks.h"

#include "../Settings.h"

typedef void (* PrepareUnitOrdersFn)( CDotaPlayer*, DotaUnitOrder_t, int, Vector, int, PlayerOrderIssuer_t, CDotaBaseNPC*, bool, bool );


static const char* Order2String( DotaUnitOrder_t order )
{
    switch( (int)order ){
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_NONE );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_MOVE_TO_POSITION );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_MOVE_TO_TARGET );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_ATTACK_MOVE );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_ATTACK_TARGET );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_POSITION );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_TARGET );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_TARGET_TREE );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_NO_TARGET );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_TOGGLE );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_HOLD_POSITION  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_TRAIN_ABILITY  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_DROP_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_GIVE_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PICKUP_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PICKUP_RUNE  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PURCHASE_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_SELL_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_DISASSEMBLE_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_MOVE_ITEM  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_STOP  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_TAUNT  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_BUYBACK  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_GLYPH  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_RUNE  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PING_ABILITY  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_MOVE_TO_DIRECTION  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PATROL  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_RADAR  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CONTINUE  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_RIVER_PAINT  );
        CASE_STRING( DotaUnitOrder_t::DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT  );
        default:
            return "ERROR: UNKNOWN ORDER TYPE!\n";
    }
}
static const char* Issuer2String( PlayerOrderIssuer_t issuer )
{
    switch( (int)issuer ){
        CASE_STRING( DOTA_ORDER_ISSUER_SELECTED_UNITS );
        CASE_STRING( DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY );
        CASE_STRING( DOTA_ORDER_ISSUER_HERO_ONLY );
        CASE_STRING( DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY );
        default:
            return "UNKNOWN ISSUER";
    }
}
static const char* Queue2String( OrderQueueBehavior_t behavior )
{
    switch( (int)behavior ){
        CASE_STRING( DOTA_ORDER_QUEUE_DEFAULT );
        CASE_STRING( DOTA_ORDER_QUEUE_NEVER );
        CASE_STRING( DOTA_ORDER_QUEUE_ALWAYS );
        default:
            return "UNKNOWN QUEUE BEHAVIOR";
    }
}

bool lastWasVector = false;
long lastVectorCmd = 0;
Vector targetPosition;

void Hooks::PrepareUnitOrders( CDotaPlayer *thisptr, DotaUnitOrder_t order, int targetIndex, Vector movePosition, int abilityIndex, PlayerOrderIssuer_t orderIssuer,
                               CDotaBaseNPC *entity, bool queue, bool showEffects ) {
    //std::raise(SIGINT);

    if( mc_retarget_orders->GetBool() && order == DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_POSITION ){
        /*
        if( targetIndex ){
            targetIndex = mc_ent_select->GetInt();
        }*/
        movePosition.x = mc_custom_x->GetFloat();
        movePosition.y = mc_custom_y->GetFloat();
        movePosition.z = 1000.0f;
    }

    /*
    if( mc_command_repeater->GetBool() ){
        MC_PRINTF("Repeating 30x\n");
        engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
        engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
        for( int i = 0; i < 30; i++ ){
            localPlayerVMT->GetOriginalMethod<PrepareUnitOrdersFn>(442)( thisptr, order, targetIndex, movePosition, abilityIndex, orderIssuer, entity, queue, queueBehavior, showEffects );
        }
        MC_PRINTF("done.\n");
    }*/

    if( mc_log_prepareunitorders->GetBool() ){
        Util::Log( "Order: %s\nEntity: (%p)[%s]\nTargetIndex: %d\nPosition: (%f,%f,%f)\nAbility Index: %d\nIssuer: %s\nQueue? %s\nShowEffects? %s\n\n",
                   Order2String(order),
                   (void*)entity, entity ? entity->Schema_DynamicBinding()->bindingName: "nil",
                   targetIndex,
                   movePosition.x, movePosition.y, movePosition.z,
                   abilityIndex,
                   Issuer2String(orderIssuer),
                   queue? "yes" : "no",
                   showEffects? "yes" : "no" );
    }

    if( entity ){
        //Vector origin = entity->C_BaseEntity__WorldSpaceCenter();
        //Util::Log( "Entity origin @ (%f,%f,%f)\n", origin.x, origin.y, origin.z );
    }

    localPlayerVMT->GetOriginalMethod<PrepareUnitOrdersFn>(442)( thisptr, order, targetIndex, movePosition, abilityIndex, orderIssuer, entity, queue, showEffects );
}