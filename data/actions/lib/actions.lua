function doDestroyItem(target)
	if not target:isItem() then
		return false
	end

	local itemType = ItemType(target:getId())
	if not itemType:isDestroyable() then
		return false
	end
	
	if math.random(1,10) <= 3 then
		target:transform(itemType:getDestroyTarget())
		target:decay()
		target:getPosition():sendMagicEffect(CONST_ME_BLOCKHIT)
	else
		target:getPosition():sendMagicEffect(CONST_ME_POFF)
	end
	
	return true
end