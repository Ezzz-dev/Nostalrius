function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32732, y = 31634, z = 07})
		creature:getPlayer():setTown(Town("Ab'Dendriel"))
		Game.sendMagicEffect({x = 32732, y = 31634, z = 07}, 13)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32607, y = 31681, z = 07})
	Game.sendMagicEffect({x = 32607, y = 31681, z = 07}, 14)
end
