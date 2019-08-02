#include "Protobuf.h"

#include "Util.h" // log

/* adapted from: https://stackoverflow.com/questions/23963978/c-protobuf-how-to-iterate-through-fields-of-message/35294011 */
void Util::Protobuf::LogMessageContents( const google::protobuf::Message *m, int tabNum ) {
    const google::protobuf::Descriptor *desc       = m->GetDescriptor();
    const google::protobuf::Reflection *refl       = m->GetReflection();
    std::string temp;

    if( !desc || !refl ){
        return;
    }

    int fieldCount= desc->field_count();

    if( fieldCount <= 0 ){
        Util::Log("{ (Empty Msg) }\n");
        return;
    }

    Util::Log("%s {\n", desc->full_name().c_str());
    for( int tabs = 0; tabs < tabNum; tabs++ ){ Util::Log("  "); }

    for(int i=0; i<fieldCount; i++) {
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( i > 0 ){
            for( int tabs = 0; tabs < tabNum; tabs++ ){ Util::Log("  "); }
        }
        Util::Log("%s %s: ", field->type_name(), field->name().c_str());
        switch( field->type() ){
            case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%f)\n", j, refl->GetRepeatedDouble( *m, field, j ) );
                    }
                } else {
                    Util::Log("%f\n", refl->GetDouble( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_FLOAT:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%f)\n", j, refl->GetRepeatedFloat( *m, field, j ) );
                    }
                } else {
                    Util::Log("%f\n", refl->GetFloat( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_INT64:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%lld)\n", j, refl->GetRepeatedInt64( *m, field, j ) );
                    }
                } else {
                    Util::Log( "%lld\n", refl->GetInt64( *m, field ) );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_UINT64:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%lld)\n", j, refl->GetRepeatedUInt64( *m, field, j ) );
                    }
                } else {
                    Util::Log("%lld\n", refl->GetUInt64( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_INT32:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%d)\n", j, refl->GetRepeatedInt32( *m, field, j ) );
                    }
                } else {
                    Util::Log("%d\n", refl->GetInt32( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_FIXED64:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%lld)\n", j, refl->GetRepeatedUInt64( *m, field, j ) );
                    }
                } else {
                    Util::Log("%lld\n", refl->GetUInt64( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_FIXED32:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)(-%d)\n", j, refl->GetRepeatedUInt32( *m, field, j ) );
                    }
                } else {
                    Util::Log("%d\n", refl->GetUInt32( *m, field ));
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_BOOL:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%s)\n", j, refl->GetRepeatedBool( *m, field, j ) ? "true" : "false" );
                    }
                } else {
                    Util::Log("%s\n", refl->GetBool( *m, field ) ? "true" : "false" );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_STRING:
                Util::Log("String parsing is busted.\n");
                /*
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-(%s)\n", j, refl->GetRepeatedString( *m, field, j ).c_str() );
                    }
                } else {
                    temp = refl->GetString( *m, field );
                    Util::Log("(%s)\n", temp.c_str());
                }*/
                break;
            case google::protobuf::FieldDescriptor::TYPE_GROUP: // deprecated
                Util::Log("We found a group tag!\n");
                break;
            case google::protobuf::FieldDescriptor::TYPE_MESSAGE: {
                if ( field->is_repeated( ) ) {
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        const google::protobuf::Message &mfield = refl->GetRepeatedMessage( *m, field, j );
                        google::protobuf::Message *mcopy = mfield.New();
                        mcopy->CopyFrom(mfield);
                        Util::Protobuf::LogMessageContents( mcopy, tabNum + 1);
                        delete mcopy;
                    }
                } else {
                    const google::protobuf::Message &mfield = refl->GetMessage( *m, field );
                    google::protobuf::Message *mcopy = mfield.New();
                    mcopy->CopyFrom(mfield);
                    Util::Protobuf::LogMessageContents( mcopy, tabNum + 1);
                    delete mcopy;
                }
            }
                break;
            case google::protobuf::FieldDescriptor::TYPE_BYTES:
                Util::Log("Byte array found!\n");
                break;
            case google::protobuf::FieldDescriptor::TYPE_UINT32:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%d\n", refl->GetRepeatedUInt32( *m, field, j ) );
                    }
                } else {
                    Util::Log("%d\n", refl->GetUInt32( *m, field ) );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_ENUM:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%s\n", refl->GetRepeatedEnum( *m, field, j )->full_name().c_str() );
                    }
                } else {
                    Util::Log("%s\n", refl->GetEnum( *m, field )->full_name().c_str() );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_SFIXED32:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%d\n", refl->GetRepeatedInt32( *m, field, j ) );
                    }
                } else {
                    Util::Log("%d\n", refl->GetInt32( *m, field ) );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_SFIXED64:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%lld\n", refl->GetRepeatedInt64( *m, field, j ) );
                    }
                } else {
                    Util::Log("%lld\n", refl->GetInt64( *m, field ) );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_SINT32:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%d\n", refl->GetRepeatedInt32( *m, field , j ) );
                    }
                } else {
                    Util::Log("%d\n", refl->GetInt32( *m, field ) );
                }
                break;
            case google::protobuf::FieldDescriptor::TYPE_SINT64:
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize( *m, field ); j++ ){
                        Util::Log("repeated:(#%d)-%lld\n", refl->GetRepeatedInt64( *m, field, j ) );
                    }
                } else {
                    Util::Log("%lld\n", refl->GetInt64( *m, field ) );
                }
                break;

            default:
                Util::Log("Can't tell Value! Unknown Type!\n");
                break;
        }
    }
    for( int tabs = 0; tabs < std::max(0, tabNum-1); tabs++ ){ Util::Log("  "); }
    Util::Log("}\n");
}

bool Util::Protobuf::EditFieldTraverseInt32( google::protobuf::Message *msg, const char *name, int32_t value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedInt32( msg, field, j, value );
                }
            } else {
                refl->SetInt32( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseInt32( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseInt32( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseUInt32( google::protobuf::Message *msg, const char *name, uint32_t value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedUInt32( msg, field, j, value );
                }
            } else {
                refl->SetUInt32( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseUInt32( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseUInt32( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseInt64( google::protobuf::Message *msg, const char *name, int64_t value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedInt64( msg, field, j, value );
                }
            } else {
                refl->SetInt64( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseInt64( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseInt64( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseUInt64( google::protobuf::Message *msg, const char *name, uint64_t value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedUInt64( msg, field, j, value );
                }
            } else {
                refl->SetUInt64( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseUInt64( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseUInt64( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseFloat( google::protobuf::Message *msg, const char *name, float value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedFloat( msg, field, j, value );
                }
            } else {
                refl->SetFloat( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseFloat( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseFloat( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseDouble( google::protobuf::Message *msg, const char *name, double value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedDouble( msg, field, j, value );
                }
            } else {
                refl->SetDouble( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseDouble( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseDouble( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseBool( google::protobuf::Message *msg, const char *name, bool value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedBool( msg, field, j, value );
                }
            } else {
                refl->SetBool( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseBool( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseBool( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseString( google::protobuf::Message *msg, const char *name, std::string value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedString( msg, field, j, value );
                }
            } else {
                refl->SetString( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseString( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseString( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

bool Util::Protobuf::EditFieldTraverseEnumValue( google::protobuf::Message *msg, const char *name, int value ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    if( !desc || !refl )
        return false;

    bool foundTarget = false;
    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    refl->SetRepeatedEnumValue( msg, field, j, value );
                }
            } else {
                refl->SetEnumValue( msg, field, value );
            }
            foundTarget = true;
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse

            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    foundTarget |= EditFieldTraverseEnumValue( mfield, name, value );
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                foundTarget |= EditFieldTraverseEnumValue( mfield, name, value );
            }
        }
    }

    return foundTarget;
}

std::optional<int32_t> Util::Protobuf::GetFieldTraverseInt32( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<int32_t> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetInt32( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseInt32( mfield, name );
        }
    }

    return ret;
}

std::optional<uint32_t> Util::Protobuf::GetFieldTraverseUInt32( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<uint32_t> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetUInt32( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseUInt32( mfield, name );
        }
    }

    return ret;
}

std::optional<int64_t> Util::Protobuf::GetFieldTraverseInt64( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<int64_t> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetInt64( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseInt64( mfield, name );
        }
    }

    return ret;
}

std::optional<uint64_t> Util::Protobuf::GetFieldTraverseUint64( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<uint64_t> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetUInt64( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseUint64( mfield, name );
        }
    }

    return ret;
}

std::optional<float> Util::Protobuf::GetFieldTraverseFloat( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<float> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetFloat( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseFloat( mfield, name );
        }
    }

    return ret;
}


std::optional<double> Util::Protobuf::GetFieldTraverseDouble( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<double> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetDouble( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseDouble( mfield, name );
        }
    }

    return ret;
}

std::optional<bool> Util::Protobuf::GetFieldTraverseBool( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<bool> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetBool( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseBool( mfield, name );
        }
    }

    return ret;
}

std::optional<std::string> Util::Protobuf::GetFieldTraverseString( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<std::string> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetString( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseString( mfield, name );
        }
    }

    return ret;
}

std::optional<int> Util::Protobuf::GetFieldTraverseEnumValue( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::optional<int> ret = std::nullopt;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field || field->is_repeated() ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( !field->is_repeated() ){
                return refl->GetEnumValue( *msg, field );
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
            ret = GetFieldTraverseEnumValue( mfield, name );
        }
    }

    return ret;
}

























































std::vector<int32_t> Util::Protobuf::GetRepeatedFieldTraverseInt32( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<int32_t> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_INT32 ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedInt32( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetInt32( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type INT32!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<int32_t> more = GetRepeatedFieldTraverseInt32( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<int32_t> more = GetRepeatedFieldTraverseInt32( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<uint32_t> Util::Protobuf::GetRepeatedFieldTraverseUInt32( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<uint32_t> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_UINT32 ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedUInt32( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetUInt32( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_UINT32!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<uint32_t> more = GetRepeatedFieldTraverseUInt32( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<uint32_t> more = GetRepeatedFieldTraverseUInt32( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}


std::vector<int64_t> Util::Protobuf::GetRepeatedFieldTraverseInt64( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<int64_t> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_INT64 ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedInt64( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetInt64( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_INT64!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<int64_t> more = GetRepeatedFieldTraverseInt64( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<int64_t> more = GetRepeatedFieldTraverseInt64( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<uint64_t> Util::Protobuf::GetRepeatedFieldTraverseUInt64( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<uint64_t> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_UINT64 ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedUInt64( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetUInt64( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_UINT64!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<uint64_t> more = GetRepeatedFieldTraverseUInt64( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<uint64_t> more = GetRepeatedFieldTraverseUInt64( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<float> Util::Protobuf::GetRepeatedFieldTraverseFloat( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<float> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_FLOAT ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedFloat( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetFloat( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_FLOAT!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<float> more = GetRepeatedFieldTraverseFloat( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<float> more = GetRepeatedFieldTraverseFloat( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<double> Util::Protobuf::GetRepeatedFieldTraverseDouble( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<double> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_DOUBLE ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedDouble( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetDouble( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_DOUBLE!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<double> more = GetRepeatedFieldTraverseDouble( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<double> more = GetRepeatedFieldTraverseDouble( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<bool> Util::Protobuf::GetRepeatedFieldTraverseBool( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<bool> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_BOOL ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedBool( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetBool( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_BOOL!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<bool> more = GetRepeatedFieldTraverseBool( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<bool> more = GetRepeatedFieldTraverseBool( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<std::string> Util::Protobuf::GetRepeatedFieldTraverseString( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<std::string> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_STRING ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedString( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetString( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_STRING!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<std::string> more = GetRepeatedFieldTraverseString( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<std::string> more = GetRepeatedFieldTraverseString( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}

std::vector<int> Util::Protobuf::GetRepeatedFieldTraverseEnumValue( google::protobuf::Message *msg, const char *name ) {
    const google::protobuf::Descriptor *desc       = msg->GetDescriptor();
    const google::protobuf::Reflection *refl       = msg->GetReflection();

    std::vector<int> ret;
    if( !desc || !refl )
        return ret;

    int fieldCount = desc->field_count();
    for( int i = 0; i < fieldCount; i++ ){
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if( !field ) continue;

        if( !strcmp( field->name().c_str(), name ) ){
            if( field->type() == google::protobuf::FieldDescriptor::TYPE_ENUM ){
                if( field->is_repeated() ){
                    for( int j = 0; j < refl->FieldSize(*msg, field); j++ ){
                        ret.push_back( refl->GetRepeatedEnumValue( *msg, field, j ) );
                    }
                } else {
                    ret.push_back( refl->GetEnumValue( *msg, field ) );
                }
            } else {
                Util::Log("FIELD (%s) is NOT type TYPE_ENUM!\n", name);
            }
        }

        if( field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE ){ // recurse
            if( field->is_repeated() ){
                for( int j = 0; j < refl->FieldSize( *msg, field ); j++ ){
                    google::protobuf::Message *mfield = refl->MutableRepeatedMessage( msg, field, j );
                    std::vector<int> more = GetRepeatedFieldTraverseEnumValue( mfield, name );
                    for( size_t k = 0; k < more.size(); k++ ){
                        ret.push_back( more[k] );
                    }
                }
            } else {
                google::protobuf::Message *mfield = refl->MutableMessage( msg, field );
                std::vector<int> more = GetRepeatedFieldTraverseEnumValue( mfield, name );
                for( size_t k = 0; k < more.size(); k++ ){
                    ret.push_back( more[k] );
                }
            }
        }
    }

    return ret;
}













