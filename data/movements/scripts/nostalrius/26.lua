function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		item:transform(430, 1)
		item:decay()
		Game.removeItemOnMap({x = 32796, y = 31594, z = 05}, 1270)
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(431, 1)
		item:decay()
		doRelocate({x = 32796, y = 31594, z = 05},{x = 32797, y = 31594, z = 05})
		Game.createItem(1270, 1, {x = 32796, y = 31594, z = 05})
	end
end
