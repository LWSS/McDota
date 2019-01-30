#include "hooks.h"
#include <csignal>

#include "../Utils/util.h"
#include "../settings.h"

typedef void (* PrepareUnitOrdersFn)( CDotaPlayer*, DotaUnitOrder_t, int, Vector, int, PlayerOrderIssuer_t, CDotaBaseNPC*, bool, OrderQueueBehavior_t, bool );

static const char* Order2String( DotaUnitOrder_t order )
{
    // r12
    switch( order ){
        case DOTA_UNIT_ORDER_NONE:
            return "DOTA_UNIT_ORDER_NONE";
        case DOTA_UNIT_ORDER_MOVE_TO_POSITION:
            return "DOTA_UNIT_ORDER_MOVE_TO_POSITION";
        case DOTA_UNIT_ORDER_MOVE_TO_TARGET:
            return "DOTA_UNIT_ORDER_MOVE_TO_TARGET";
        case DOTA_UNIT_ORDER_ATTACK_MOVE:
            return "DOTA_UNIT_ORDER_ATTACK_MOVE";
        case DOTA_UNIT_ORDER_ATTACK_TARGET:
            return "DOTA_UNIT_ORDER_ATTACK_TARGET";
        case DOTA_UNIT_ORDER_CAST_POSITION:
            return "DOTA_UNIT_ORDER_CAST_POSITION";
        case DOTA_UNIT_ORDER_CAST_TARGET:
            return "DOTA_UNIT_ORDER_CAST_TARGET";
        case DOTA_UNIT_ORDER_CAST_TARGET_TREE:
            return "DOTA_UNIT_ORDER_CAST_TARGET_TREE";
        case DOTA_UNIT_ORDER_CAST_NO_TARGET:
            return "DOTA_UNIT_ORDER_CAST_NO_TARGET";
        case DOTA_UNIT_ORDER_CAST_TOGGLE:
            return "DOTA_UNIT_ORDER_CAST_TOGGLE";
        case DOTA_UNIT_ORDER_HOLD_POSITION :
            return "DOTA_UNIT_ORDER_HOLD_POSITION";
        case DOTA_UNIT_ORDER_TRAIN_ABILITY :
            return "DOTA_UNIT_ORDER_TRAIN_ABILITY";
        case DOTA_UNIT_ORDER_DROP_ITEM :
            return "DOTA_UNIT_ORDER_DROP_ITEM";
        case DOTA_UNIT_ORDER_GIVE_ITEM :
            return "DOTA_UNIT_ORDER_GIVE_ITEM";
        case DOTA_UNIT_ORDER_PICKUP_ITEM :
            return "DOTA_UNIT_ORDER_PICKUP_ITEM";
        case DOTA_UNIT_ORDER_PICKUP_RUNE :
            return "DOTA_UNIT_ORDER_PICKUP_RUNE";
        case DOTA_UNIT_ORDER_PURCHASE_ITEM :
            return "DOTA_UNIT_ORDER_PURCHASE_ITEM";
        case DOTA_UNIT_ORDER_SELL_ITEM :
            return "DOTA_UNIT_ORDER_SELL_ITEM";
        case DOTA_UNIT_ORDER_DISASSEMBLE_ITEM :
            return "DOTA_UNIT_ORDER_DISASSEMBLE_ITEM";
        case DOTA_UNIT_ORDER_MOVE_ITEM :
            return "DOTA_UNIT_ORDER_MOVE_ITEM";
        case DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO :
            return "DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO";
        case DOTA_UNIT_ORDER_STOP :
            return "DOTA_UNIT_ORDER_STOP";
        case DOTA_UNIT_ORDER_TAUNT :
            return "DOTA_UNIT_ORDER_TAUNT";
        case DOTA_UNIT_ORDER_BUYBACK :
            return "DOTA_UNIT_ORDER_BUYBACK";
        case DOTA_UNIT_ORDER_GLYPH :
            return "DOTA_UNIT_ORDER_GLYPH";
        case DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH :
            return "DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH";
        case DOTA_UNIT_ORDER_CAST_RUNE :
            return "DOTA_UNIT_ORDER_CAST_RUNE";
        case DOTA_UNIT_ORDER_PING_ABILITY :
            return "DOTA_UNIT_ORDER_PING_ABILITY";
        case DOTA_UNIT_ORDER_MOVE_TO_DIRECTION :
            return "DOTA_UNIT_ORDER_MOVE_TO_DIRECTION";
        case DOTA_UNIT_ORDER_PATROL :
            return "DOTA_UNIT_ORDER_PATROL";
        case DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION :
            return "DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION";
        case DOTA_UNIT_ORDER_RADAR :
            return "DOTA_UNIT_ORDER_RADAR";
        case DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK :
            return "DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK";
        case DOTA_UNIT_ORDER_CONTINUE :
            return "DOTA_UNIT_ORDER_CONTINUE";
        case DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED :
            return "DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED";
        case DOTA_UNIT_ORDER_CAST_RIVER_PAINT :
            return "DOTA_UNIT_ORDER_CAST_RIVER_PAINT";
        case DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT :
            return "DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT";
        default:
            return "ERROR: UNKNOWN ORDER TYPE!\n";
    }
}
static const char* Issuer2String( PlayerOrderIssuer_t issuer )
{
    switch( issuer ){
        case DOTA_ORDER_ISSUER_SELECTED_UNITS:
            return "DOTA_ORDER_ISSUER_SELECTED_UNITS";
        case DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY:
            return "DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY";
        case DOTA_ORDER_ISSUER_HERO_ONLY:
            return "DOTA_ORDER_ISSUER_HERO_ONLY";
        case DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY:
            return "DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY";
        default:
            return "UNKNOWN ISSUER";
    }
}
static const char* Queue2String( OrderQueueBehavior_t behavior )
{
    switch( behavior ){
        case DOTA_ORDER_QUEUE_DEFAULT:
            return "DOTA_ORDER_QUEUE_DEFAULT";
        case DOTA_ORDER_QUEUE_NEVER:
            return "DOTA_ORDER_QUEUE_NEVER";
        case DOTA_ORDER_QUEUE_ALWAYS:
            return "DOTA_ORDER_QUEUE_ALWAYS";
        default:
            return "UNKNOWN QUEUE BEHAVIOR";
    }
}

bool lastWasVector = false;
long lastVectorCmd = 0;
Vector targetPosition;

void Hooks::PrepareUnitOrders( CDotaPlayer *thisptr, DotaUnitOrder_t order, int targetIndex, Vector movePosition, int abilityIndex, PlayerOrderIssuer_t orderIssuer,
                               CDotaBaseNPC *entity, bool queue, OrderQueueBehavior_t queueBehavior, bool showEffects ) {
    //std::raise(SIGINT);

    if( mc_retarget_orders->GetBool() ){
        if( targetIndex ){
            targetIndex = mc_ent_select->GetInt();
        }
    }

    if( mc_command_repeater->GetBool() ){
        cvar->ConsoleDPrintf("Repeating 30x\n");
        engine->GetNetChannelInfo()->SetMaxRoutablePayloadSize(99999999);
        engine->GetNetChannelInfo()->SetMaxBufferSize(NetChannelBufType_t::BUF_DEFAULT, 99999999);
        for( int i = 0; i < 30; i++ ){
            localPlayerVMT->GetOriginalMethod<PrepareUnitOrdersFn>(435)( thisptr, order, targetIndex, movePosition, abilityIndex, orderIssuer, entity, queue, queueBehavior, showEffects );
        }
        cvar->ConsoleDPrintf("done.\n");
    }

    if( mc_log_prepareunitorders->GetBool() ){
        Util::Log( "Order: %s\nEntity: (%p)[%s]\nTargetIndex: %d\nPosition: (%f,%f,%f)\nAbility Index: %d\nIssuer: %s\nQueue? %s\nQueueBehavior: %s\nShowEffects? %s\n\n",
                   Order2String(order),
                   (void*)entity, entity ? entity->Schema_DynamicBinding()->bindingName: "nil",
                   targetIndex,
                   movePosition.x, movePosition.y, movePosition.z,
                   abilityIndex,
                   Issuer2String(orderIssuer),
                   queue? "yes" : "no",
                   Queue2String(queueBehavior),
                   showEffects? "yes" : "no" );
    }

    if( entity ){
        //Vector origin = entity->C_BaseEntity__WorldSpaceCenter();
        //Util::Log( "Entity origin @ (%f,%f,%f)\n", origin.x, origin.y, origin.z );
    }

    localPlayerVMT->GetOriginalMethod<PrepareUnitOrdersFn>(435)( thisptr, order, targetIndex, movePosition, abilityIndex, orderIssuer, entity, queue, queueBehavior, showEffects );
}