function onStepIn(creature, item, position, fromPosition)
	local player = Player(creature)
	player:setStorageValue(260, 1)
end
