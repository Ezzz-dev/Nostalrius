local fieldIds = {
	2118, 2119, 2120, 2121, 2122, 2123, 2124, 2125,
	2126, 2127, 2131, 2132, 2133, 2134, 2135
}

function onCastSpell(creature, variant, isHotkey)
	local position = Variant.getPosition(variant)
	local tile = Tile(position)
	local field = tile and tile:getItemByType(ITEM_TYPE_MAGICFIELD)

	if field and table.contains(fieldIds, field:getId()) then
		field:remove()
		position:sendMagicEffect(CONST_ME_POFF)
		return true
	end
	
	for _, id in ipairs(fieldIds) do
		field = tile and tile:getItemById(id)
		if field then
			field:remove()
			position:sendMagicEffect(CONST_ME_POFF)
			return true
		end
	end
	
	creature:sendCancelMessage(RETURNVALUE_NOTPOSSIBLE)
	creature:getPosition():sendMagicEffect(CONST_ME_POFF)
	return false
end