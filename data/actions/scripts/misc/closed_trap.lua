function onUse(player, item, fromPosition, target, toPosition)
	if Tile(item:getPosition()):hasFlag(TILESTATE_PROTECTIONZONE) then
		item:getPosition():sendMagicEffect(3)
	else
		item:transform(3482, 1)
		item:decay()
	end
	return true
end
