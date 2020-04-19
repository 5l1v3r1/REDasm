#include "gotomodel.h"
#include "../../themeprovider.h"
#include "../../../convert.h"
#include <redasm/plugins/assembler/assembler.h>
#include <redasm/support/demangler.h>
#include <redasm/support/utils.h>
#include <redasm/context.h>

GotoModel::GotoModel(QObject *parent) : DisassemblerModel(parent) { }

void GotoModel::setDisassembler(RDDisassembler* disassembler)
{
    this->beginResetModel();
    DisassemblerModel::setDisassembler(disassembler);
    this->endResetModel();
}

QVariant GotoModel::data(const QModelIndex &index, int role) const
{
    if(!m_disassembler)
        return QVariant();

    // REDasm::ListingItem item = m_disassembler->document()->items()->at(index.row());

    // if(role == Qt::DisplayRole)
    // {
    //     if(index.column() == 0)
    //         return Convert::to_qstring(REDasm::String::hex(item.address, r_asm->bits()));
    //     if(index.column() == 1)
    //         return this->itemName(item);
    //     if(index.column() == 2)
    //         return this->itemType(item);
    // }
    // else if(role == Qt::TextAlignmentRole)
    // {
    //     if(index.column() == 2)
    //         return Qt::AlignCenter;
    // }
    // else if(role == Qt::ForegroundRole)
    // {
    //     if(index.column() == 0)
    //         return THEME_VALUE("address_list_fg");

    //     if(index.column() == 1)
    //         return this->itemColor(item);
    // }

    return QVariant();
}

QVariant GotoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        if(section == 0)      return "Address";
        else if(section == 1) return "Name";
        else if(section == 2) return "Type";
    }

    return DisassemblerModel::headerData(section, orientation, role);
}

int GotoModel::columnCount(const QModelIndex &) const { return 3; }
int GotoModel::rowCount(const QModelIndex &) const { return 0; } //return r_disasm ? r_doc->items()->size() : 0; }

QColor GotoModel::itemColor(const REDasm::ListingItem& item) const
{
    if(item.is(REDasm::ListingItem::SegmentItem))  return THEME_VALUE("segment_fg");
    if(item.is(REDasm::ListingItem::FunctionItem)) return THEME_VALUE("function_fg");
    if(item.is(REDasm::ListingItem::TypeItem))     return THEME_VALUE("type_fg");

    // if(item.is(REDasm::ListingItem::SymbolItem))
    // {
    //     const REDasm::Symbol* symbol = r_doc->symbol(item.address);

    //     if(!symbol) return QColor();
    //     if(symbol->isString()) return THEME_VALUE("string_fg");
    //     return THEME_VALUE("data_fg");
    // }

    return QColor();
}

QString GotoModel::itemName(const REDasm::ListingItem& item) const
{
    // if(item.is(REDasm::ListingItem::SegmentItem))
    // {
    //     const REDasm::Segment* segment = r_doc->segment(item.address);
    //     if(segment) return Convert::to_qstring(segment->name());
    // }
    // else if(item.is(REDasm::ListingItem::FunctionItem) || item.is(REDasm::ListingItem::SymbolItem))
    // {
    //     const REDasm::Symbol* symbol = r_doc->symbol(item.address);
    //     if(symbol) return Convert::to_qstring(REDasm::Demangler::demangled(symbol->name));
    // }
    // else if(item.type == REDasm::ListingItem::TypeItem)
    //     return Convert::to_qstring(r_doc->type(item.address));

    // return QString();
}

QString GotoModel::itemType(const REDasm::ListingItem& item) const
{
    switch(item.type)
    {
        case REDasm::ListingItem::SegmentItem:  return "SEGMENT";
        case REDasm::ListingItem::FunctionItem: return "FUNCTION";
        case REDasm::ListingItem::TypeItem:     return "TYPE";
        case REDasm::ListingItem::SymbolItem:   return "SYMBOL";
        default: break;
    }

    return QString();
}
